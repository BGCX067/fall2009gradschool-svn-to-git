/*
 * CS6390
 * OO Type System
 * Puyan Lotfi
 *
 * OO Principals Used:
 *   - Inheretance (All TYPEDEFs types and built in Operations Inheret from TYPEDEF)
 *   - Polymorphism (Everything has an Eval method that evaluates the type of the part of the expression it is responsible for.)
 *   - Encapsulation and delegation of resposibilities to varioys classes.
 *       - TYPEDEF and children handle storage of typpdefs and evaluations of expressions.
 *       - VARDECL handles storage of VARDECLS.
 *       - Expression and children handle storage of a tree representing the S-Expression like format use for expresions.
 */

using System;
using System.IO;
using System.Collections.Generic;

public class SyntacticException : ArgumentException
{
    public SyntacticException() : base() {}
    public SyntacticException(string message) : base(message) {}
    public SyntacticException(string message, Exception innerException) : base(message, innerException) {}
    public SyntacticException(string message, string paramName) : base(message, paramName) {}
    public SyntacticException(string message, string paramName, Exception innerException) : base(message, paramName, innerException) {}
}

public class SemanticException : ArgumentException
{
    public SemanticException() : base() {}
    public SemanticException(string message) : base(message) {}
    public SemanticException(string message, Exception innerException) : base(message, innerException) {}
    public SemanticException(string message, string paramName) : base(message, paramName) {}
    public SemanticException(string message, string paramName, Exception innerException) : base(message, paramName, innerException) {}
}

public abstract class TYPEDEF
{
    public string Name { get; set; }
    public string Type { get; set; }

    public abstract string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable);

    /*
     * Parses TYPEDEF commands (First token, then delegates rest to specific TYPEDEF implementations).
     * Populates typedef table.
     */
    public static TYPEDEF Parse(string code, Dictionary <string, TYPEDEF> typedefTable)
    {
        if (String.IsNullOrEmpty(code)) throw new ArgumentNullException("code");
        if (null == typedefTable) throw new ArgumentNullException("typedefTable");

        string[] tokens = code.Split(new char[]{' ', '\t'}, StringSplitOptions.RemoveEmptyEntries);

        if (tokens.Length < 3) throw new ArgumentException("TYPEDEF statements must consist of at least three tokens (TYPEDEF <NAME> <TYPE>), received: " + code);
        if (tokens[0].ToUpper() != "TYPEDEF") throw new ArgumentException("TYPEDEFs must start with keyword TYPEDEF, but received: " + tokens[0]);

        TYPEDEF parsedType = null;
        string Type =  tokens[2].ToUpper();

        if (Type == "BASIC")
        {
            parsedType = new BASIC(tokens, typedefTable);
        }
        else if (Type == "PRODUCT")
        {
            parsedType = new PRODUCT(tokens, typedefTable);
        }
        else if (Type == "SUM")
        {
            parsedType = new SUM(tokens, typedefTable);
        }
        else if (Type == "SEQUENCE")
        {
            parsedType = new SEQUENCE(tokens, typedefTable);
        }
        else if (Type == "FUNCTION")
        {
            parsedType = new FUNCTION(tokens, typedefTable);
        }
        else if (Type == "SUBTYPE")
        {
            parsedType = new SUBTYPE(tokens, typedefTable);
        }
        else
        {
            throw new SyntacticException("Not a valid TYPEDEF: " + code);
        }

        return parsedType;
    }
}

public class ACCESSP : TYPEDEF
{
    public ACCESSP(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "ACCESSP";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {

        if (expList.Count != 2 && !(expList[0] is ListExpression)) throw new SemanticException("ACCESSP Operator requires an expression and field parameter (ACCESSP <exp> <field>).");

        object param1;
        object param2;

        if (expList.Count !=2 && expList[0] is ListExpression)
        {
            param1 = expList[0].First();
            param2 = expList[0].Rest();
        }
        else
        {
            param1 = expList[0];
            param2 = expList[1];
        }

        string prodtype = (param1 as Expression).Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(prodtype)) throw new SemanticException("A Product of type " + prodtype + " was never defined, please add a TYPEDEF " + prodtype + " PRODUCT ... above.");

        if (typedefTable[prodtype].Type != "PRODUCT" && 
                typedefTable[prodtype].Name != "MKPROD" && 
                typedefTable[prodtype].Type != "SUM" && 
                typedefTable[prodtype].Name != "TREATAS" &&
                typedefTable[prodtype].Type != "SUBTYPE" &&
                typedefTable[prodtype].Name != "EMBED")
            throw new SemanticException("Expression " + (param1 as Expression) + " evaluates to type " + prodtype + " but ACCESSP  requires a second parameter type of " + "PRODUCT");

        PRODUCT prod = typedefTable[prodtype] as PRODUCT;


        if (null == prod || 
                typedefTable[prodtype].Name == "MKPROD" || 
                 typedefTable[prodtype].Name == "TREATAS"  ||
                 typedefTable[prodtype].Name == "EMBED" )
        {
            ListExpression foobar = (param2 as ListExpression);
            prodtype = foobar.expList[0].Variable;

            VARDECL vardecl  = symbolTable[prodtype];
            prod = typedefTable[vardecl.Type] as PRODUCT;

            string prod_field = foobar.expList[foobar.expList.Count -1].Variable;

            return prod.ArgPairs[prod_field];

        }

        if (null == prod) throw new SemanticException("First param to ACCESSP is not actually a PRODUCT.");

        VariableExpression varexp = (param2 as VariableExpression);

        if (null == varexp) throw new SemanticException("Second param to ACCESSP is not actually a field value, but an expression");

        if (!prod.ArgPairs.ContainsKey(varexp.Variable)) throw new SemanticException("The PRODUCT " + prod.Name + " does not have a field with name " + varexp.Variable + ".");

        return prod.ArgPairs[varexp.Variable];
    }
}

public class MKPROD : TYPEDEF
{
    public MKPROD(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "MKPROD";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count < 3) throw new SemanticException("MKPROD Operator requires a product name, a field, and at least one expression (MKPROD <product name> <field> <exp> ...).");

        string prodname = expList[0].Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(prodname)) throw new SemanticException("A Product of type " + prodname + " was never defined, please add a TYPEDEF " + prodname + " PRODUCT ... above.");

        if (typedefTable[prodname].Type != "PRODUCT")
            throw new SemanticException("Expression " + expList[0] + " evaluates to type " + typedefTable[prodname].Type + " but expected type PRODUCT.");

        PRODUCT prod = typedefTable[prodname] as PRODUCT;

        if (null == prod) throw new SemanticException("First param to MKPROD is not actually a PRODUCT.");

        return prod.Name;
    }
}

public class TREATAS : SUM
{

    public TREATAS() { }

    public TREATAS(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "TREATAS";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count < 2) throw new SemanticException("TREATAS Operator requires a SUM name, a field, and one expression (TREATAS <product name> <field> <exp> ).");
        
        string sumname = expList[0].Eval(typedefTable, symbolTable);
       
        if (!typedefTable.ContainsKey(sumname)) throw new SemanticException("A SUM of type " + sumname + " was never defined, please add a TYPEDEF " + sumname + " PRODUCT ... above.");

        if (typedefTable[sumname].Type != "SUM")
            throw new SemanticException("Expression " + expList[0] + " evaluates to type " + typedefTable[sumname].Type + " but expected type SUM.");

        SUM sum = typedefTable[sumname] as SUM;

        if (null == sum) throw new SemanticException("First param to TREATAS is not actually a SUM.");
        

        VariableExpression varexp = (expList[1] as VariableExpression); // fieldname

        if (null == varexp) throw new SemanticException("Second param to TREATAS is not actually a field value, but an expression of some sort.");

        if (!sum.ArgPairs.ContainsKey(varexp.Variable)) throw new SemanticException("The SUM " + sum.Name + " does not have a field with name " + varexp.Variable + ".");

        return sum.ArgPairs[varexp.Variable];

    }
}

public class EMBED : SUM
{
    public EMBED(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "EMBED";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count != 2) throw new SemanticException("EMBED Operator requires a SUM name, a field, and one expression (EMBED <product name> <field> <exp> ).");

        string sumname = expList[0].Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(sumname)) throw new SemanticException("A SUM of type " + sumname + " was never defined, please add a TYPEDEF " + sumname + " PRODUCT ... above.");

        if (typedefTable[sumname].Type != "SUM")
            throw new SemanticException("Expression " + expList[0] + " evaluates to type " + typedefTable[sumname].Type + " but expected type SUM.");

        SUM sum = typedefTable[sumname] as SUM;

        if (null == sum) throw new SemanticException("First param to EMBED is not actually a SUM.");

        string exptype = expList[1].Eval(typedefTable, symbolTable);

        VariableExpression varexp = (expList[1] as VariableExpression); // fieldname

        if (null == varexp) throw new SemanticException("Second param to EMBED is not actually a field value, but an expression of some sort.");

        if (!sum.ArgPairs.ContainsValue(exptype)) throw new SemanticException("The SUM " + sum.Name + " can not be expressed as type " + exptype + ".");

        return sum.Name;
    }
}

public class HEAD : TYPEDEF
{
    public HEAD(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "HEAD";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count != 1) throw new SemanticException("HEAD Operator requires one expression (HEAD <exp> ).");

        string seqname = expList[0].Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(seqname)) throw new SemanticException("A SEQUENCE of type " + seqname + " was never defined, please add a TYPEDEF " + seqname + " SEQUENCE ... above.");

        if (typedefTable[seqname].Type != "SEQUENCE")
            throw new SemanticException("Expression " + expList[0] + " evaluates to type " + typedefTable[seqname].Type + " but expected type SUM.");

        SEQUENCE seq = typedefTable[seqname] as SEQUENCE;

        if (null == seq) throw new SemanticException("First param to HEAD is not actually a SEQUENCE.");

        return seq.Name;
    }
}

public class TAIL : TYPEDEF
{
    public TAIL(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "TAIL";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count != 1) throw new SemanticException("TAIL Operator requires one expression (TAIL <exp> ).");

        string seqname = expList[0].Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(seqname)) throw new SemanticException("A SEQUENCE of type " + seqname + " was never defined, please add a TYPEDEF " + seqname + " SEQUENCE ... above.");

        if (typedefTable[seqname].Type != "SEQUENCE")
            throw new SemanticException("Expression " + expList[0] + " evaluates to type " + typedefTable[seqname].Type + " but expected type SUM.");

        SEQUENCE seq = typedefTable[seqname] as SEQUENCE;

        if (null == seq) throw new SemanticException("First param to TAIL is not actually a SEQUENCE.");

        return seq.Name;
    }
}


public class CONS : TYPEDEF
{
    public CONS(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "CONS";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count != 2) throw new SemanticException("CONS Operator requires one expression (CONS <exp1> <exp2> ).");

        string seqname1 = expList[0].Eval(typedefTable, symbolTable);
        string seqname2 = expList[1].Eval(typedefTable, symbolTable);

        if (!typedefTable.ContainsKey(seqname1)) throw new SemanticException("There is no SEQUENCE type named " + seqname1);
        if (!typedefTable.ContainsKey(seqname2)) throw new SemanticException("There is no SEQUENCE type named " + seqname2);

        TYPEDEF seqdef1 = typedefTable[seqname1];
        TYPEDEF seqdef2 = typedefTable[seqname2];

        if (seqdef1.Type != "SEQUENCE") throw new SemanticException("CONS operator is only allowed on two SEQUENCEs");
        if (seqdef2.Type != "SEQUENCE") throw new SemanticException("CONS operator is only allowed on two SEQUENCEs");

        if ((seqdef1 as SEQUENCE).AliasedType != (seqdef2 as SEQUENCE).AliasedType) throw new SemanticException("Type Error: Can not CONS two different types together.");

        return (seqdef1 as SEQUENCE).Name;
    }
}

public class NIL : TYPEDEF
{
    public NIL(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = "NIL";
        Type = "DYNAMIC";

        if (!typedefTable.ContainsKey(Name))
            typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (expList.Count < 1) throw new SemanticException("NIL Operator requires one expression (NIL <exp1> <exp2> ).");

        string seqname1 = expList[0].Variable;

        if (!typedefTable.ContainsKey(seqname1)) throw new SemanticException("There is no SEQUENCE type named " + seqname1);

        TYPEDEF seqdef1 = typedefTable[seqname1];

        if (seqdef1.Type != "SEQUENCE") throw new SemanticException("NIL operator is only allowed on two SEQUENCEs");

        return (seqdef1 as SEQUENCE).Name;
    }
}

public class BASIC : TYPEDEF
{
    public BASIC(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        Name = tokens[1];
        Type = tokens[2].ToUpper();
        typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        return Name;
    }
}

public class PRODUCT : TYPEDEF
{
    public Dictionary<string, string> ArgPairs { get; set; }
    
    public PRODUCT() {}
    
    public PRODUCT(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        ArgPairs = new Dictionary<string, string>();
        Name = tokens[1];
        Type = tokens[2].ToUpper();
        
        for (int i = 3; i < tokens.Length; )
        {
            string name;
            string type;
            
            if ( i < tokens.Length)
                name = tokens[i++];
            else
                break;
            
            if ( i < tokens.Length)
                type = tokens[i++];
            else
                break;
            
            ArgPairs.Add(name, type);
        }
        
        typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        return Name;
    }
}

public class SUM : PRODUCT
{
    

    public SUM() {}
    
    public SUM(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        ArgPairs = new Dictionary <string, string>();
        Name = tokens[1];
        Type = tokens[2].ToUpper();
        
        for (int i = 3; i < tokens.Length; )
        {
            string name;
            string type;
            
            if ( i < tokens.Length)
                name = tokens[i++];
            else
                break;
            
            if ( i < tokens.Length)
                type = tokens[i++];
            else
                break;
            
            ArgPairs.Add(name, type);
        }
        
        typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        return Name;
    }
}

public class SEQUENCE : TYPEDEF
{
    public string AliasedType { get; set; }
    
    public SEQUENCE(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        if (tokens.Length < 4) throw new SyntacticException("SEQUENCE types require 4 tokens (TYPEDEF <NAME> <TYPE> <ALIAS>.");
        
        Name = tokens[1];
        Type = tokens[2].ToUpper();
        AliasedType = tokens[3];
        
        if (!typedefTable.ContainsKey(AliasedType))
        {
            throw new SemanticException("SEQUENCE defines an alias of type " + AliasedType + " that was never previously defined.");
        }
        
        typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        return Name;
    }
}

public class FUNCTION : TYPEDEF
{
    public string InType { get; set; }
    public string OutType { get; set; }
    
    public FUNCTION(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        if (tokens.Length < 5) throw new SyntacticException("FUNCTION types require 5 tokens (TYPEDEF <NAME> <TYPE> <DOMAIN> <RANGE>.");
        
        Name = tokens[1];
        Type = tokens[2].ToUpper();
        InType = tokens[3];
        OutType = tokens[4];
        
        if (!typedefTable.ContainsKey(InType)) throw new SemanticException("FUNCTION takes a domain type " + InType + " that was never previously defined.");
        
        if (!typedefTable.ContainsKey(OutType)) throw new SemanticException("FUNCTION returns a range type " + OutType + " that was never previously defined.");
        
        typedefTable.Add(Name, this);
    }
    
    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        //if (expList.Count > 2) throw new SemanticException("Function " + Name + " like all functions should only be passed one domain parameter.");
        
        string intype = expList[0].Eval(typedefTable, symbolTable);
        
        if (intype != this.InType) throw new SemanticException("Expression " + expList[0] + " evaluates to type " + intype + " but function " + Name  + " requires a domain type of " + InType);
        
        return OutType;
    }
}

public class SUBTYPE : PRODUCT
{
    public string Product { get; set;}

    public SUBTYPE(string[] tokens, Dictionary <string, TYPEDEF> typedefTable)
    {
        if (tokens.Length < 4) throw new SyntacticException("SUBTYPE types require at least 4 tokens (TYPEDEF <NAME> <TYPE> <PRODUCT> ...");

        ArgPairs = new Dictionary<string, string>();

        Name = tokens[1];
        Type = tokens[2].ToUpper();
        Product = tokens[3];
        
        for (int i = 4; i < tokens.Length; )
        {
            string name;
            string type;
            
            if ( i < tokens.Length)
                name = tokens[i++];
            else
                break;
            
            if ( i < tokens.Length)
                type = tokens[i++];
            else
                break;
            
            ArgPairs.Add(name, type);
        }
        
        typedefTable.Add(Name, this);
    }

    public override string Eval(List<Expression> expList, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        return Name;
    }
}

public class VARDECL
{
    public string Name { get; set; }
    public string Type { get; set; }
    
    public VARDECL(string code, Dictionary <string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (String.IsNullOrEmpty(code)) throw new ArgumentNullException("code");
        if (null == typedefTable) throw new ArgumentNullException("typedefTable");
        if (null == symbolTable) throw new ArgumentNullException("symbolTable");
        
        string[] tokens = code.Split(new char[]{' ', '\t'}, StringSplitOptions.RemoveEmptyEntries);
        
        if (tokens.Length < 3) throw new ArgumentException("VARDECL statements must consist of at least three tokens (VARDECL <NAME> <TYPE>), received: " + code);
        if (tokens[0].ToUpper() != "VARDECL") throw new ArgumentException("VARDECLs must start with keyword VARDECL, but received: " + tokens[0]);
        
        Name = tokens[1];
        Type = tokens[2];
        
        if (!typedefTable.ContainsKey(Type)) throw new SemanticException("Defining a VARDECL of type " + Type + " that was never previously defined.");
        
        symbolTable.Add(Name, this);
    }
}

public abstract class Expression
{

    public abstract string Variable { get; set;}
    public abstract Expression First();
    public abstract Expression Rest();
    public abstract void Print();
    public abstract string Eval(Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable);
}

public class ListExpression : Expression
{
    public List<Expression> expList { get; set;}
    
    public override string Variable
    {
        get
        {
            return First().Variable;
        }

        set
        {

        }
    }

    public ListExpression()
    {
        expList = new List<Expression>();
    }
   
    public override Expression First()
    {
        return expList[0];
    }

    public override Expression Rest()
    {
        return new ListExpression { expList = expList.GetRange(1,expList.Count-1)};
    }

    public override void Print()
    {
        Console.Write("(");
        
        foreach (Expression exp in expList)
        {
            exp.Print();
        }
            
        Console.Write(")");
    }
    
    public override string Eval(Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        TYPEDEF type = typedefTable[symbolTable[(expList[0] as VariableExpression).Variable].Type];
        return type.Eval(expList.GetRange(1, expList.Count -1), typedefTable, symbolTable);
    }
}

public class VariableExpression : Expression
{
    public override string Variable { get; set;}
    public override void Print()
    {
        Console.Write(Variable + " ");
    }
  
    public override Expression First()
    {
        return this;
    }

    public override Expression Rest()
    {
        return null;
    }

    public override string Eval(Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (typedefTable.ContainsKey(Variable) && !symbolTable.ContainsKey(Variable))
        {
            return typedefTable[Variable].Name;
        }

        if (!symbolTable.ContainsKey(Variable)) throw new SemanticException("No such VARDECL: " + Variable);
        
        VARDECL decl = symbolTable[Variable];
        
        if (!typedefTable.ContainsKey(decl.Type)) throw new SemanticException("No such TYPEDEF: " + decl.Type);
        
        return typedefTable[decl.Type].Name;
    }
}

public static class ExpressionEval
{
    public static ListExpression ParseExpressionListStr (string code, out string remCode)
    {
        ListExpression expList = new ListExpression ();
        char[] codeArr = code.ToCharArray ();
        int subExpStart = 0;

        for (int i = 0; i < code.Length; i++)
        {
            if (' ' == codeArr[i] ||
                '\t' == codeArr[i])
            {
                string var = code.Substring (subExpStart, i - subExpStart);
                
                if (!String.IsNullOrEmpty(var))
                {
                    VariableExpression subExp = new VariableExpression { Variable = var};
                    expList.expList.Add(subExp);
                }
                
                subExpStart = i + 1;
                continue;
            }
            
            if (')' == codeArr[i])
            {
                string var = code.Substring(subExpStart, i - subExpStart);
                
                if (!String.IsNullOrEmpty(var))
                {
                    VariableExpression subExp = new VariableExpression { Variable = var};
                    expList.expList.Add(subExp);
                }
                
                remCode = code.Substring (i + 1);
                //return expList;
            }
            
            if ('(' == codeArr[i])
            {
                code = code.Substring (i + 1);
                expList.expList.Add (ParseExpressionListStr (code, out remCode));
                code = remCode;
            }
        }
        
        remCode = "";
        return expList;
        
    }
    
    public static Expression ParseExpressionStr(string code)
    {
        if (String.IsNullOrEmpty(code)) throw new ArgumentNullException("code");
        
        if (!code.Contains("(") && !code.Contains(")") && !code.Contains(" ") && !code.Contains("\t"))
        {
            return new VariableExpression {Variable = code};
        }
        else
        {
            string remCode = "";
            // TODO: Check leading paren
            Expression exp = ParseExpressionListStr(code.Substring(1), out remCode);
            
            //Console.WriteLine("Remaining code: " + remCode);
            
            return exp;
        }
    }
    
    public static void Eval (string code, Dictionary<string, TYPEDEF> typedefTable, Dictionary<string, VARDECL> symbolTable)
    {
        if (String.IsNullOrEmpty (code))
            throw new ArgumentNullException ("code");
        if (null == typedefTable)
            throw new ArgumentNullException ("typedefTable");
        if (null == symbolTable)
            throw new ArgumentNullException ("symbolTable");
        

        if (!typedefTable.ContainsKey("ACCESSP"))
        {
            new ACCESSP(null, typedefTable);
            new VARDECL("VARDECL ACCESSP ACCESSP", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("MKPROD"))
        {
            new MKPROD(null, typedefTable);
            new VARDECL("VARDECL MKPROD MKPROD", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("TREATAS"))
        {
            new TREATAS(null, typedefTable);
            new VARDECL("VARDECL TREATAS TREATAS", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("EMBED"))
        {
            new EMBED(null, typedefTable);
            new VARDECL("VARDECL EMBED EMBED", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("HEAD"))
        {
            new HEAD(null, typedefTable);
            new VARDECL("VARDECL HEAD HEAD", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("TAIL"))
        {
            new TAIL(null, typedefTable);
            new VARDECL("VARDECL TAIL TAIL", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("CONS"))
        {
            new CONS(null, typedefTable);
            new VARDECL("VARDECL CONS CONS", typedefTable, symbolTable);
        }

        if (!typedefTable.ContainsKey("NIL"))
        {
            new NIL(null, typedefTable);
            new VARDECL("VARDECL NIL NIL", typedefTable, symbolTable);
        }

        int LPAREN_count = 0;
        int RPAREN_count = 0;
        
        foreach (char c in code.ToCharArray())
        {
            switch (c)
            {
            case '(': LPAREN_count++;
                break;
            case ')': RPAREN_count++;
                break;
            default:
                break;
            }
        }
        
        if (LPAREN_count != RPAREN_count) throw new SyntacticException("Expression does not have a matching set of Parens.");
        
        Expression exp = ParseExpressionStr (code);
        
        Console.WriteLine(code + " => " + exp.Eval(typedefTable, symbolTable));
        
        // exp.Print();
        
    }
}


class Program
{
    public static void Main (string[] args)
    {
        if (args.Length < 1 || !File.Exists (args[0]))
        {
            Console.WriteLine ("tail.exe file.tail");
            System.Environment.Exit (0);
        }
        
        
        Dictionary<string, TYPEDEF> typedefTable = new Dictionary<string, TYPEDEF> ();
        Dictionary<string, VARDECL> symbolTable = new Dictionary<string, VARDECL> ();
        
        
        string[] lines = File.ReadAllLines (args[0]);
        
        // Organize the TAIL contructs into lists.
        // Then process the lists.
        // I assume that if correct syntax is used and that
        // only TAIL expressions, typedefs, vardecls or empty lines
        // can exist in a tail file.
        int lineCount = 0;
        foreach (string line in lines)
        {
            try
            {
                if (line.ToUpper ().StartsWith ("TYPEDEF"))
                {
                    TYPEDEF.Parse (line, typedefTable);
                }
                else if (line.ToUpper ().StartsWith ("VARDECL"))
                {
                    new VARDECL (line, typedefTable, symbolTable);
                }
                else if (!String.IsNullOrEmpty (line))
                {
                    ExpressionEval.Eval(line, typedefTable, symbolTable);
                }
            }
            catch (SemanticException semex)
            {
                Console.WriteLine("Semantic Exception on line " + lineCount + " : " + semex.Message);
            }
            catch (SyntacticException synex)
            {
                Console.WriteLine("Syntax Exceptionon line " + lineCount + " : " + synex.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Exception: " + ex.Message);
            }
            
            lineCount++;
        }
        
        /*
        foreach (string str in typedefTable.Keys)
        {
            Console.WriteLine("Type: " + str);
        }
        
        Console.WriteLine("");
        
        foreach (string str in symbolTable.Keys)
        {
            Console.WriteLine("Var: " + str);
        }*/
    }
}











// The following is my report:
//

/*
// I have managed to have a test case for every base type.
// I also make sure that the built in functions for SUMs and PRODUCTs
//    work together can can be called inside each other.
//
// 
// 
// My output prints out the typedefed name that the expression resolves to,
//   and not the built-in type that the typedef targets.


// The following is my Input:


TYPEDEF Int  BASIC
TYPEDEF Bool BASIC
TYPEDEF Fun  FUNCTION Int Bool
TYPEDEF Fun2  FUNCTION Int Int
TYPEDEF Foo PRODUCT x Int y Bool
TYPEDEF SumFoo SUM q Int w Bool
TYPEDEF Prod PRODUCT a Fun b Fun
TYPEDEF m SEQUENCE Int
TYPEDEF mn SEQUENCE Int
TYPEDEF sub1 SUBTYPE Prod c Int b Int n Bool

VARDECL ii Int
VARDECL fi Fun
VARDECL f Fun
VARDECL pi Prod
VARDECL g Fun2
VARDECL i Int
VARDECL j Int
VARDECL b Bool
VARDECL p Foo
VARDECL h SumFoo
VARDECL gh sub1
VARDECL seqq mn


(gh)
(seqq)
(ACCESSP gh c)
(MKPROD pi a fi b fi)
(ACCESSP pi a)
(ACCESSP Prod a)
(ACCESSP (MKPROD pi a fi b fi) a)
(p)
(HEAD m)
(CONS m m)
(NIL m)
(CONS m (CONS m (NIL m)))
(HEAD (CONS m (CONS m (NIL m))))
(TAIL (CONS m (CONS m (NIL m))))
(HEAD (TAIL (CONS m (CONS m (NIL m)))))
(HEAD (TAIL (CONS mn (CONS mn (NIL mn)))))
(NIL m)
(ACCESSP (TREATAS h q h) q)
(ACCESSP (EMBED h q h) q)
(TREATAS h w h)
(EMBED h j)
(ACCESSP p y)
(MKPROD p x i y b)
(f i)
(f j)
(f (g i))
(f (g (g i)))
(f (g j))
(g (g (g (g (g j)))))

// The following is my output:

(gh) => sub1
(seqq) => mn
(ACCESSP gh c) => Int
(MKPROD pi a fi b fi) => Prod
(ACCESSP pi a) => Fun
(ACCESSP Prod a) => Fun
(ACCESSP (MKPROD pi a fi b fi) a) => Fun
(p) => Foo
(HEAD m) => m
(CONS m m) => m
(NIL m) => m
(CONS m (CONS m (NIL m))) => m
(HEAD (CONS m (CONS m (NIL m)))) => m
(TAIL (CONS m (CONS m (NIL m)))) => m
(HEAD (TAIL (CONS m (CONS m (NIL m))))) => m
(HEAD (TAIL (CONS mn (CONS mn (NIL mn))))) => mn
(NIL m) => m
(ACCESSP (TREATAS h q h) q) => Int
(ACCESSP (EMBED h q h) q) => Int
(TREATAS h w h) => Bool
(EMBED h j) => SumFoo
(ACCESSP p y) => Bool
(MKPROD p x i y b) => Foo
(f i) => Bool
(f j) => Bool
(f (g i)) => Bool
(f (g (g i))) => Bool
(f (g j)) => Bool
(g (g (g (g (g j))))) => Int
*/


