# MALLOC

Thread safe, tested on MacOS with common softs such as ls, vim, the python3 interpreter...

## Mmap and not sbrk

Despite Epitech subjects recommended the use of brk(2), having to deploy our malloc on MacOS we had to remove the authorisation to use it, because of the way <a href='https://www.google.com/search?q=apple+source+sbrk&ie=utf-8&oe=utf-8&client=firefox-b-ab'>it has been reimplemented on MacOS</a>:

```
void *brk(void *x)
{
	errno = ENOMEM;
	return((void *)-1);
}
```
(This is the true brk implementation currently on every apple branded device)

## Malloc

According to the subject's specifications, malloc(size_t s) divides memory type into three categories depending on s, the division uses arbitrary numbers witch were mine to define.  
Tiny (<= 128o), Small (<= 1024) and Big for above.

Still according to the subject, asking for a Tiny or Small allocation will create a plage cumulating at least 100 blocks sized Tiny or Small respectivelly.
