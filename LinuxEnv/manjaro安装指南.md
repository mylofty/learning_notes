# vmware安装manjaro系统
## 一、系统配置
** 安装必须选中文，否则输入法很难弄**
###1 切换源、更新系统

```bash
#更新源
sudo pacman-mirrors -i -c China -m rank 	#更新镜像排名
sudo pacman -Syy                          				#更新数据源

#添加archlinuxcn源
gedit /etc/pacman.conf
#插入以下内容
[archlinuxcn]
SigLevel = Optional TrustedOnly
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch  

sudo pacman -Syy	#编辑完配置文件更新数据源

#安装archlinuxcn-keyring
sudo pacman -S archlinuxcn-keyring
sudo pacman -Syyu 	#至此开始系统更新
sudo reboot -f
sudo poweroff
```

### 2 安装vmware-tools
那么有一个非常简单的方法是使用github上的一个包，vmware-tools-patches 
```
$ git clone https://github.com/rasa/vmware-tools-patches.git
$ sudo pacman -R open-vm-tools
$ cd vmware-tools-patches
$ sudo ./patched-open-vm-tools.sh
```
就可以了。这个包可以自动匹配vm版本安装适合的tools并且安装各种补丁包。 之后重启

### 3 修改目录映射
前面已经说过，为了输入法安装上的方便，我们安装的是中文系统，所以我们需要将中文目录修改为英文
```
vim .config/user-dirs.dirs

XDG_DESKTOP_DIR="$HOME/Desktop"
XDG_DOWNLOAD_DIR="$HOME/Download"
XDG_TEMPLATES_DIR="$HOME/Templates"
XDG_PUBLICSHARE_DIR="$HOME/Public"
XDG_DOCUMENTS_DIR="$HOME/Documents"
XDG_MUSIC_DIR="$HOME/Music"
XDG_PICTURES_DIR="$HOME/Pictures"
XDG_VIDEOS_DIR="$HOME/Videos"
```

## 二、基础软件安装
### 1 安装浏览器、编辑器
```bash
#安装Chrome
sudo pacman -S google-chrome
#安装vim
sudo pacman -S vim
```
### 2 安装输入法
最好一开始安装选择中文，否则此处会导致终端、文件管理器等地方无法输入中文
选择的是搜狗拼音输入法
```bash
sudo pacman -S fcitx-sogoupinyin
sudo pacman -S fcitx-im 
sudo pacman -S fcitx-configtool
```
修改vim ～/.xprofile，在最下方添加：(不要编辑成了profile)
```bash
export GTK_IM_MODULE=fcitx
export QT_IM_MODULE=fcitx
export XMODIFIERS="@im=fcitx"
```
重启生效

### 3 安装shadowsocks

```bash
sudo pacman -Sy --noconfirm shadowsocks-libev
sudo mkdir /etc/shadowsocks
sudo vim /etc/shadowsocks/config.json
```
config.json配置如下
```bash
{
	"server": "144.34.205.127",
	"server_port": 443,
	"password": "M2JmY2IwNWDZM",
	"method": "aes-256-cfb",
	"local_address":"127.0.0.1",
	"local_port":1080
}
```
查看服务
```bash
sudo systemctl start shadowsocks-libev@config  	#开启服务
sudo systemctl status shadowsocks-libev@config	#查看服务
sudo systemctl enable shadowsocks-libev@config  	#开机启动
```
安装http代理polipo
```bash
sudo pacman -S polipo 
sudo vim /etc/polipo/config 
```
config中添加如下配置
```bash
socksParentProxy = "localhost:1080"
socksProxyType = socks5 
```
另外，在~/.bashrc中添加环境变量
```bash
# http proxy
export http_proxy=http://localhost:8123
export https_proxy=http://localhost:8123
```

查看polipo服务
```bash
sudo systemctl start polipo.service
sudo systemctl status polipo.service
sudo systemctl enable polipo.service
```
