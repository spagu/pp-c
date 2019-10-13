<p align="center"><img src="images/pushpanel-logo.png" alt="pushpanel"></p>

# pp - PushPanel CLI (C version)

[![Build Status](https://travis-ci.org/spagu/pp-c.svg?branch=master)](https://travis-ci.org/spagu/pp-c)&nbsp;
[![Downloads](https://img.shields.io/github/downloads/spagu/pp-c/total.svg)](https://github.com/spagu/pp-c/releases) 
[![Downloads](https://img.shields.io/github/release/spagu/pp-c.svg?label=Release)](https://github.com/spagu/pp-c/releases) 


`pp` is a command line interface for [PushPanel.io](https://pushpanel.io) services. ( C version )

---

## Requirements
- Local Linux/BSD shell access
- Account on [PushPanel.io](https://pushpanel.io)
- Unblock Firewall on port 443 so your console is able to communicate with dash.pushpanel.io:443
- CLANG/GCC/C compiler language installed

## Install
```sh
git clone https://github.com/spagu/pp.git
cd pp && ./configure && make install
```

## Configuration
Create file `.pushpanel` in your home directory with a Token from Panel

## Usage
Commands are controlled via server.

### Command-Line 

```
pp project list
pp project create projectname repotype projecttype --initialversion=
pp project release projectname
pp project revision projectname
pp project unpublish projectname
pp project archive projectname
pp website create domainname
pp website deploy development to production domainname
```

### Project management
Add file called `pushpanel.yaml` inside your repository with a controlled content:

```yaml
projects:

    name: supername

website:
    production:
        domainname:domanname.co.uk
    staging:
        domainname:stg.domanname.co.uk
    development:
        domainname:dev.domanname.co.uk
```
### How to help

Did you find any bugs or have some suggestions?
- Feel free to open [new issue](https://github.com/spagu/pp/issues/new).

Do you want to contribute to the project?
- Fork the repository and open a pull request. [Here](https://github.com/spagu/pp/projects/1) you can find TODO features.

---
## Author
`pp` was developed by [PushPanel](https://pushpanel.io).

## License
`pp` is available under the [BSD](./LICENSE) license.


