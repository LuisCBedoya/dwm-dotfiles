#!/bin/bash

i="sudo apt install -y"
i1="sudo apt install --no-install-recommends -y"
s="sudo"
#gestor de video - mpv
#gestor de imagenes sxiv
#gestor de archivos pcmanfm
#screenshot flameshot
#gestor de aplicaciones dmenu
#wm - dwm
#trasparencia picom
#notificaciones dunst
#bar slstatus
#terminal kitty
#explorador chromium
#editor IDE neovim
#editor de dibujo drawing


echo "|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|"
echo "|Workpace Installer|"
echo "|__________________|"
echo ""
echo ""
sleep 2s
echo "Introduzca contraseña para continuar"
sudo -k
if sudo true; then
	clear
	echo "Iniciando Instalacion..."
	sleep 2s
else
	clear
	echo "Debe introduccir contraseña para continuar"
	exit 1
fi


# backports repository and pipewire, wireplumber
cd
$s cp -r dwm-dotfiles/config/files/pipewire-upstream.list /etc/apt/sources.list.d/
$s cp -r dwm-dotfiles/config/files/wireplumber-upstream.list /etc/apt/sources.list.d/
$s cp -r dwm-dotfiles/config/files/bullseye-backports.list /etc/apt/sources.list.d/
$s apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 25088A0359807596


$s apt update -y && $s apt upgrade -y

# paquetes xorg -------------------------------------------------
$i xorg xbacklight xbindkeys xinput xorg-dev

# $i amd64-microcode --------------------------------------------
$i intel-microcode

#nvidia driver -------------------------------------------------------------------------------
$i nvidia-driver

#Paquetes para compilar ------------------------------------------
$i linux-headers-$(uname -r) build-essential make automake pkg-config cmake autoconf git curl wget unzip tar gzip python3-pip
$i libncurses-dev flex bison openssl libssl-dev dkms libelf-dev pkg-config liblz4-tool

# Network File Tools/System Events --------------------------------
$i dialog mtools dosfstools avahi-daemon acpi acpid gvfs-backends

#enable services ----------------------------------------------
sudo systemctl enable avahi-daemon
sudo systemctl enable acpid

# Codecs  -----------------------------------------------------------------------------------------------------
$i alsa-utils pavucontrol alsa-firmware-loaders alsa-oss alsa-tools alsamixergui volumeicon-alsa pacman paprefs pavumeter pulseaudio-utils ffmpeg2theora sound-icons
$i lame libdvdnav4 libfaac0 libmad0 libmp3lame0 libquicktime2 libstdc++5 libxvidcore4 twolame vorbis-tools x264
$i gstreamer1.0-x gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-alsa gstreamer1.0-pulseaudio gstreamer1.0-tools

#pipewire --------------------------------------------------------
$i libfdk-aac2 libldacbt-{abr,enc}2 libopenaptx0
$i gstreamer1.0-pipewire libpipewire-0.3-{0,dev,modules} libspa-0.2-{bluetooth,dev,jack,modules} pipewire{,-{audio-client-libraries,pulse,bin,locales,tests}}
$i pipewire-doc
$i libpipewire-module-x11-bell

#wirepumbler ----------------------------------------------------
$i wireplumber{,-doc} gir1.2-wp-0.4 libwireplumber-0.4-{0,dev}
$i wireplumber-locales

#enable pipewire -----------------------------------------------
systemctl --user --now enable pipewire{,-pulse}.{socket,service}

#enable wirepumbler --------------------------------------------
systemctl --user --now enable wireplumber.service

#fonts -------------------------------------------------------------
$i fonts-noto fonts-noto-cjk fonts-noto-extra fonts-noto-color-emoji

#install cargo, npm, nodejs -----------------------------------------
$i nodejs npm

cd
curl https://sh.rustup.rs -sSf | sh

#paquetes requeridos para picom -------------------------------------------------------------
$i libxext-dev libxcb1-dev libxcb-damage0-dev libxcb-dpms0-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-render-util0-dev libxcb-render0-dev libxcb-randr0-dev libxcb-composite0-dev libxcb-image0-dev libxcb-present-dev libxcb-glx0-dev libpixman-1-dev libdbus-1-dev libconfig-dev libgl-dev libegl-dev libpcre2-dev libevdev-dev uthash-dev libev-dev libx11-xcb-dev meson

#install picom --------------------------------------------------------------------------------
cd
git clone https://github.com/yshui/picom
cd picom/
git submodule update --init --recursive
meson setup --buildtype=release . build
ninja -C build
$s ninja -C build install

#install lsd command line
cd
wget https://github.com/lsd-rs/lsd/releases/download/0.23.1/lsd-musl_0.23.1_amd64.deb
$s dpkg -i lsd-musl_0.23.1_amd64.deb

#nvim
cd
wget https://github.com/neovim/neovim/releases/download/stable/nvim.appimage
chmod u+x nvim.appimage
$s mv nvim.appimage /usr/bin/nvim

#user packages
$i1 kitty feh ripgrep chromium sxiv pcmanfm flameshot dunst libnotify-bin

#install mpv last version
$s apt install -t bullseye-backports libdvdnav4 liblua5.2-0 libmodplug1 libopencore-amrnb0 libopencore-amrwb0 libssh-4 libvo-amrwbenc0 libxpresent1

wget https://non-gnu.uvt.nl/debian/bullseye/mpv/mpv_0.35.1+fruit.3_amd64.deb

$s dpkg -i mpv_0.35.1+fruit.3_amd64.deb

#install yt-dlp
pip3 install yt-dlp
pip3 install --upgrade yt-dlp


#user fonts
cd
$s cp -r ~/dwm-dotfiles/config/fonts/JetBrainsMonoFonts /usr/share/fonts/
$s cp -r dwm-dotfiles/config/fonts/HackerNerdFonts /usr/share/fonts/


#install suckless tools
cd
cp -r dwm-dotfiles/config/suckless ~/.config/
cd .config/suckless/dwm && $s make clean install

cd
cd .config/suckless/dmenu && $s make clean install

cd
cd .config/suckless/slstatus  && $s make clean install


#kitty files
cd
cp -r ~/dwm-dotfiles/config/kitty/ ~/.config/

#dunst files
cd
cp -r ~/dwm-dotfiles/config/dunst/ ~/.config/

#picom files
cd
cp -r ~/dwm-dotfiles/config/picom/ ~/.config/

#mpv files
cd
cp -r ~/dwm-dotfiles/config/mpv/ ~/.config/

#zathura files
cd
cp -r ~/dwm-dotfiles/config/zathura/ ~/.config/

#wallpapers
cd
cp -r ~/dwm-dotfiles/wallpapers/ ~/.local/share/


sudo apt autoremove

printf "\e[1;32mReinicia para aplicar cambios.\e[0m\n"
