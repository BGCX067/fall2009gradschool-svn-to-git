#ifndef ABSTRACT_FRAME_H
#define ABSTRACT_FRAME_H

#include "Visitor.h"

class FrameIterator;

//-----------------------------------------------------------------------------
//	AbstractFrame
//-----------------------------------------------------------------------------

class AbstractFrame
{
public:

	virtual ~AbstractFrame() { } // pure virtual destructor causes compile err

	virtual void accept(Visitor & v) = 0;

	virtual FrameIterator* begin() = 0;
	virtual FrameIterator* end() = 0;
};

//-----------------------------------------------------------------------------
//	FrameIterator
//-----------------------------------------------------------------------------

class FrameIterator
{
public:

	virtual ~FrameIterator() { } // pure virtual destructor causes compile err

	virtual AbstractFrame* operator*() = 0;
	virtual const AbstractFrame* operator*() const = 0;

	virtual FrameIterator& operator++() = 0;

	virtual bool operator==(const FrameIterator & rhs) const;
	virtual bool operator!=(const FrameIterator & rhs) const;

protected:

	virtual AbstractFrame* getFrame() const = 0;
};

//-----------------------------------------------------------------------------
//	FrameIteratorBridge
//-----------------------------------------------------------------------------

class FrameIteratorBridge
{
public:

	FrameIteratorBridge(FrameIterator* iter);
	virtual ~FrameIteratorBridge();

	virtual AbstractFrame* operator*();
	virtual AbstractFrame* operator*() const;

	virtual bool operator==(const FrameIteratorBridge & rhs) const;
	virtual bool operator!=(const FrameIteratorBridge & rhs) const;

	virtual FrameIteratorBridge& operator++();

protected:

	FrameIterator* iter;
};

#endif