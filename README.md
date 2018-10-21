## auto-files-bkup

### Installation process

Copy this text and bash it!
```bash
    $ wget -q https://raw.githubusercontent.com/JakariaBlaine/auto_files_bkup/master/install ; wget -q https://raw.githubusercontent.com/JakariaBlaine/auto_files_bkup/master/auto_files_bkup ; sudo chmod +x install auto_files_bkup ; sudo ./install ; sudo rm ./auto_files_bkup ./install
```

Or, if you have cloned the repository already, do this.
```bash
    $ sudo ./install.sh
```

### Build process

#### External libraries used
* Boost 1.68.0

After having boost 1.68.0 installed.

```bash
    $ make build
    $ sudo make init # optional - to install the compiled executable file (./build/auto_files_bkup)
```

### How to use
After installation, there are two options to use the application.

Quick command:
```bash
    $ auto_files_bkup /path/to/backup 3 # 3 being the delay between one backup to next.
```
Extended usage:
```bash
    $ auto_files_bkup
```

A configuration file(auto_bkup_configs.txt) will be generated. Edit that file as your wish and run this command again.
```bash
    $ auto_files_bkup
```
