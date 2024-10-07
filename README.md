## minishell
This project is about creating a simple shell. You will learn a lot about processes and file descriptors.

This is the first group project in the 42 core curriculum, that was done by myself and [davioliv]()
## How To Execute The Program
To compile the program:
```bash
$ make
```
To execute the program:
```bash
$ ./minishell
```
After that, a prompt will be presented:

![Screenshot from 2023-07-05 09-50-41](https://github.com/t-pereira06/42_minishell/assets/118270669/07d2c940-06ff-4940-b0fe-78bccb00c269)

## Rules Of The Project
Your shell should:
* Display a prompt when waiting for a new command.

* Have a working history.

* Search and launch the right executable (based on the ```$PATH``` variable or using a
relative or an absolute path).

* Not use more than one global variable

* Not interpret unclosed quotes or special characters which are not required by the
subject such as ```\``` (backslash) or ```;``` (semicolon).

* Handle ```’``` (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.

* Handle ```"``` (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).

* Implement redirections:
  * ```<``` should redirect input.
  * ```>``` should redirect output.
  * ```<<``` should be given a delimiter, then read the input until a line containing the
    delimiter is seen. However, it doesn’t have to update the history!
  * ```>>``` should redirect output in append mode.

* Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.

* Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.

* Handle ```$?``` which should expand to the exit status of the most recently executed
foreground pipeline.

* Handle ```ctrl-C```, ```ctrl-D``` and ```ctrl-\``` which should behave like in bash.

* In interactive mode:
  * ```ctrl-C``` displays a new prompt on a new line.
  * ```ctrl-D``` exits the shell.
  * ```ctrl-\``` does nothing.

* Your shell must implement the following builtins:
  * ```echo``` with option -n
  * ```cd``` with only a relative or absolute path
  * ```pwd``` with no options
  * ```export``` with no options
  * ```unset``` with no options

  * ```env``` with no options or arguments
  * ```exit``` with no options

# Grade:
![Screenshot from 2023-08-02 09-29-29](https://github.com/t-pereira06/42_minishell/assets/118270669/ed729df1-e6f6-495c-8950-d2199b4551a6)
