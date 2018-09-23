;;;; karuta-mode.el -- Major mode for Karuta script

;; THIS IS REALLY PRELIMINARY. DO NOT USE UNLESS YOU KNOW HOW TO PLAY WITH EMACS.
;; THERE ARE TOOOO MANY TODOs.

;;;; Commentary:
;;
;; Copied most of code from https://www.emacswiki.org/emacs/ModeTutorial
;; and https://www.emacswiki.org/emacs/wpdl-mode.el
;;

;;;; Code:

(defvar karuta-mode-hook nil)

(setq karuta-highlights
      '(("def\\|func" . font-lock-function-name-face)
	("var" . font-lock-constant-face)
	("int\\|object" . font-lock-keyword-face)))

(defun karuta-indent-line ()
  "Indent current line as Karuta code"
  (interactive)
  (beginning-of-line)
  (if (bobp)
      (indent-line-to 0)
    (let ((not-indented t) cur-indent)
      (if (looking-at "^[ \t]*}") ; If the line we are looking at is the end of a block, then decrease the indentation
	  (progn
	    (save-excursion
	      (forward-line -1)
	      (setq cur-indent (- (current-indentation) default-tab-width)))
	    (if (< cur-indent 0) ; We can't indent past the left margin
		(setq cur-indent 0)))
	(save-excursion
	  (while not-indented ; Iterate backwards until we find an indentation hint
	    (forward-line -1)
	    (if (looking-at "^[ \t]*}") ; This hint indicates that we need to indent at the level of the END_ token
		(progn
		  (setq cur-indent (current-indentation))
		  (setq not-indented nil))
	      (if (looking-at "^[ \t]*\\(def\\|if\\|for\\)") ; This hint indicates that we need to indent an extra level
		  (progn
		    (setq cur-indent (+ (current-indentation) default-tab-width)) ; Do the actual indenting
		    (setq not-indented nil))
		(if (bobp)
		    (setq not-indented nil)))))))
      (if cur-indent
	  (indent-line-to cur-indent)
	(indent-line-to 0))))) ; If we didn't see an indentation hint, then allow no indentation


(define-derived-mode karuta-mode fundamental-mode "karuta"
  "major mode for editing Karuta language code"
  (setq font-lock-defaults '(karuta-highlights))
  (set (make-local-variable 'indent-line-function) 'karuta-indent-line)
  (run-hooks 'karuta-mode))

(add-to-list 'auto-mode-alist '("\\.karuta\\'" . karuta-mode))
(provide 'karuta-mode)

