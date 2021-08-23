# termux-repo

My repo for termux packages.

To use, download the repo key, add it to apt and add the repo as a source:

```
curl -L -o repo.asc "https://github.com/reddit-appcompat/termux-repo/raw/main/repo.asc"
apt-key add repo.asc
curl -L -o $PREFIX/etc/apt/sources.list.d/appcompat-repo.list "https://raw.githubusercontent.com/reddit-appcompat/termux-repo/main/appcompat-repo.list"
rm repo.asc
```  
  
## Packages

### termux-user-fix
Fixes the displayed user and group name.  
To use you have to put the library path into the LD_PRELOAD environment variable.  
The best way to do this is to put 'export LD_PRELOAD=\"/data/data/com.termux/files/usr/lib/libfixuser.so:$LD_PRELOAD\" ' in your .bash_profile or .bashrc.  
  








