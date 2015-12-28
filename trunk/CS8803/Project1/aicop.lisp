(defvar aicopInputFile)
(setf aicopInputFile (open "aicop.txt"))


;; The frame registry
(defparameter globalFrameRegistry (make-hash-table))
(defparameter globalPrePostRegistry (make-hash-table))

(defstruct prepost action pre post)
(defstruct frame slots fillers)


(defparameter slots nil)
(defparameter currentaction nil)
(defparameter currentagent nil)
(defparameter currentcoagent nil)
(defparameter currentlocation nil)
(defparameter currentobject nil)
(defparameter currenttime nil)
(defparameter NEW-INTIALIZED-FRAME nil)

;;; Lets assume we use symbols as keys.
(defun add-slot (frame slot)
    (if (listp (frame-slots frame))
        (setf (frame-slots frame) (concatenate 'list (frame-slots frame) (list slot)))
        (setf (frame-slots frame) (list slot))))

(defun add-filler (frame slot filler)
    (if (not (listp (frame-slots frame)))
        (add-slot frame slot))
    (if (not (member slot (frame-slots frame)))
        (add-slot frame slot))
    (if (not (hash-table-p (frame-fillers frame)))
        (setf (frame-fillers frame) (make-hash-table)))
    (if (not (gethash slot (frame-fillers frame)))
        (setf (gethash slot (frame-fillers frame)) filler)
        (if (not (listp (gethash slot (frame-fillers frame))))
            (setf (gethash slot (frame-fillers frame)) (concatenate 'list (list filler) (list (gethash slot (frame-fillers frame)))))
            (setf (gethash slot (frame-fillers frame)) (concatenate 'list (list filler) (gethash slot (frame-fillers frame)))))))

(defun print-fillers (slots fillers)
    (if slots
        (if (symbolp (gethash (car slots) fillers))
            (write-line (concatenate 'string
                            (symbol-name (car slots))
                            ": "
                            (symbol-name (gethash (car slots) fillers))))))
    (if slots
        (print-fillers (cdr slots) fillers)))

(defun print-frames (frames)
    (write-line "----------")
    (if frames
        (if (listp frames)
            (print-fillers (frame-slots (car frames)) (frame-fillers (car frames)))
            (print-fillers (frame-slots frames) (frame-fillers frames))))
    
    (if (and frames (listp frames))
        (print-frames (cdr frames))))

(defun print-frames-by-key (key)
    (print-frames (gethash key globalFrameRegistry)))

(defun frame-has-value (frame val)
    (setf slots (frame-slots frame))
    (loop while slots do
        (if (eq (gethash (car slots) (frame-fillers frame)) val)
            (return 'true))
        
        (setf slots (cdr slots))))

(defun add-action (frame filler)
    (add-filler frame 'action filler))

(defun add-agent (frame filler)
    (add-filler frame 'agent filler))

(defun add-object (frame filler)
    (add-filler frame 'object filler))

(defun add-location (frame filler)
    (add-filler frame 'location filler))

(defun add-coagent (frame filler)
    (add-filler frame 'co-agent filler))

(defun add-time (frame filler)
    (add-filler frame 'time filler))

(defvar currentFrame)
(defun init-new-frame (action agent object location coagent time)
    (setf currentFrame (make-frame))
    
    (if (not (eq 'blank action ))
        (add-action currentFrame  action ))
    
    (if (not (eq 'blank agent))
        (add-agent currentFrame  agent))
    
    (if (not (eq 'blank object))
        (add-object currentFrame  object))
    
    (if (not (eq 'blank location))
        (add-location currentFrame  location))
    
    (if (not (eq 'blank coagent))
        (add-coagent currentFrame  coagent))
    
    (if (not (eq 'blank time))
        (add-time currentFrame  time))
    
    currentFrame)

(defun register-frame (key frame)
    (if (and key frame)
        (if (not (gethash key globalFrameRegistry))
            (setf (gethash key globalFrameRegistry) frame)
            (if (listp (gethash key globalFrameRegistry))
                (setf (gethash key globalFrameRegistry) (concatenate 'list (list frame)  (gethash key globalFrameRegistry)))
                (setf (gethash key globalFrameRegistry) (concatenate 'list (list frame)  (list (gethash key globalFrameRegistry))))))))

;;; Found this function on the internet.
(defun replace-all (string part replacement &key (test #'char=))
"Returns a new string in which all the occurences of the part 
is replaced with replacement."
    (with-output-to-string (out)
      (loop with part-length = (length part)
            for old-pos = 0 then (+ pos part-length)
            for pos = (search part string
                          :start2 old-pos
                          :test test)
            do (write-string string out
                 :start old-pos
                 :end (or pos (length string)))
            when pos do (write-string replacement out)
            while pos))) 

;;; Found this function on the internet.
; (defun string-split (split-string string)
 ; "Returns a list containing items in 'string' split from
 ; occurrences of 'split-string'."
     ; (loop with l = (length split-string)
         ; for n = 0 then (+ pos l)
         ; for pos = (search split-string string :start2 n)
         ; if pos collect (subseq string n pos)
         ; else collect (subseq string n)
     ; while pos))

(defun list-symbol-filter (filter-val lst)
    (if lst
    (cond 
        ((eq filter-val (car lst))
                (concatenate 'list (list (car lst)) (list-symbol-filter filter-val (cdr lst))))
        (t  (if (eq filter-val (car (cdr lst)))
            (concatenate 'list (list (car lst)) (list-symbol-filter filter-val (cdr lst)))
            (concatenate 'list (list (list (car lst) (car (cdr lst)))) (list-symbol-filter filter-val (cdr (cdr lst)))))))))

(defun get-line-entry (line)
    (cdar (eval
        (read-from-string
            (concatenate 'string "'(" (replace-all line "," "_" ) ")" )))))

(defvar line)


(defun aicopEntry2IntermediateLists (lst miss-state delim)
    (if (not lst)
        (if miss-state (list 'blank))
        (if (and miss-state (eq delim (car lst)))
            (concatenate 'list (list 'blank) (aicopEntry2IntermediateLists (cdr lst) (not nil) delim))
            (if (eq delim (car lst))
            (aicopEntry2IntermediateLists (cdr lst) (not nil) delim)
            (concatenate 'list (list (car lst)) (aicopEntry2IntermediateLists (cdr lst) nil delim))))))

(defun print-file (file lst)
    (setf line (read-line file nil))

    (if line
        (concatenate 'list
        lst
        (print-file file 
            (list (concatenate 'list
                (list (caar (get-line-entry line)))
                (list  (aicopEntry2IntermediateLists 
                    (list-symbol-filter '_  (car (cdar (get-line-entry line))))
                    (not nil) '_))))))
                    lst))

(defparameter aicopEntries (print-file aicopInputFile '()))

(defun entrieslen (lst) 
    (if lst 
        (concatenate 'list (list (list-length (cadar lst))) (entrieslen (cdr lst)))))

(entrieslen aicopEntries)


(defun populate-frame (entries)
    (setf currentAction (caar entries))
    (setf currentAgent (elt (cadar entries) 0))
    (setf currentObject (elt (cadar entries) 1))
    (setf currentLocation (elt (cadar entries) 2))
    (setf currentCoAgent (elt (cadar entries) 3))
    (setf currentTime (elt (cadar entries) 4))
    
    (setf new-intialized-frame
        (init-new-frame 
        currentAction
        currentAgent
        currentObject
        currentLocation
        currentCoAgent
        currentTime))
    
    (if (not (eq currentAction 'blank))
        (register-frame currentAction new-intialized-frame))
    
    (if (not (eq currentAgent 'blank))
        (register-frame currentAgent new-intialized-frame))
                
    (if (not (eq currentObject 'blank))
        (register-frame currentObject new-intialized-frame))
    
    (if (not (eq currentLocation 'blank))
        (register-frame currentLocation new-intialized-frame))
    
    (if (not (eq currentCoAgent 'blank))
        (register-frame currentCoAgent new-intialized-frame))

    (if (not (eq currentTime 'blank))
        (register-frame currentTime new-intialized-frame)))


(defun populate-frames (entries)
    (if (and entries (eq 5 (length (cadar entries))))
        (populate-frame entries))
            
    (if (and entries (eq 5 (length (cadar entries))))
        (populate-frames (cdr entries))))



(populate-frames aicopEntries)

(defun is-illegal (frame)
    (if (and (eq 'give (gethash 'action (frame-fillers frame)))
             (or (frame-has-value frame 'fake-id)
                 (frame-has-value frame 'fake-check)))
        'true)
    
    )

; more fancy code that couldn't be finished.

; (setf store-crime-pre (make-prepost 
                        ; :action 'give
                        ; :pre (list 'go-to 'give)
                        ; :post (list 'give 'suspect)))

; (is-illegal (gethash 'fake-id globalFrameRegistry))
; (is-illegal (gethash 'fake-check globalFrameRegistry))


; Hard coded pre and post conditinal list.
; Bootstrap
(defparameter events 
(list 
    
    'new-chain
    
    'researches
    'was-alerted
    'investigating
    'reported
    'not-expected
    'continuing
    'faked
    'remains
    
    'new-chain
    
    'signed-contract
    'installed
    'had-problems
    'asked-to-investigate
    'pledged-answer
    
    'new-chain
    
    'founded
    'started
    'worked-with
    'chose
    'approved
    'injected-mouse
    'treatment-mouse
    'injected-cow
    'treatment-cow
    'have-developed
    'cured-disease
    
    'new-chain

    'working-on
    'broke-ground
    'invested
    'received

    'new-chain
    
    'announced-investigation
    'discontinued-investigation
    
    'new-chain

    'voted-against
    'opposed
    'raised
    'runs-for
    'were-taken
    'print
    'requested
    'refused
    'decreased
    'drops-out
    
    'new-chain
    
    'entered-car
    'came-from
    'opened
    'pulled-from
    'attempted-snatch
    'snatch
    'hit
    'knocked-down
    'yelled
    'ran-away-without
    
    'new-chain
    
    'parked
    'walked-toward
    'grabbed
    'got-scared
    'run-away
    
    'new-chain
    
    'go-to
    'give
    'suspect
    'get-caught
    'call
    'run-away
    'chase-down
    'get-away))

(defun print-causalities (events)
    (dolist (event events)
        (if (eq 'new-chain event)
        (progn (write-line "")
        (write-line "---------- New Causal Chain ----------"))
        (print-frames (gethash event globalFrameRegistry)))))


(print-causalities events)

; Fancy code that I couldn't finish.

; (defun build-events (blob lst)
    ; (if blob
        ; (cond 
            ; ((listp   blob) (build-events-listhandler blob lst)) 
            ; ((frame-p blob) (build-events-framehandler blob lst))
            ; ((symbolp blob) (build-events-symbolhandler blob lst)))))

; (defun build-events-listhandler (blob lst)
    ; (if blob
        ; (concatenate 'list (build-events (car blob) '()) (build-events-listhandler (cdr blob) lst))))
        
; (defun build-events-framehandler (blob lst)
    ; (if blob
        ; (if (not (member blob lst))
            ; (concatenate 'list
                ; (list blob)
                ; (build-events-listhandler (get-subframes blob lst) lst)))))
        
; (defun build-events-symbolhandler (blob lst)
    ; (write-line (symbol-name blob))
    ; (if blob
        ; (if (not (member (gethash blob globalFrameRegistry) lst))
            ; (build-events (gethash blob globalFrameRegistry) lst))))

;; Naledge Bootstrap!!!
; (setf (gethash 'give globalPrePostRegistry)
            ; (list ('fake-id store-crime-pre) ('fake-check store-crime-pre)))
