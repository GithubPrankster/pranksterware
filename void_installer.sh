sudo xbps-install -S void-repo-nonfree void-repo-multilib void-repo-multilib-nonfree
sudo xbps-install -Syv
sudo xbps-install -S nano gcc make patch git curl xtools libopenal glm glfw firefox xorg-minimal xorg-fonts WindowMaker nvidia pcmanfm audacity gimp obs ffmpeg setxkbmap
git clone https://github.com/void-linux/void-packages.git
cd void-packages
./xbps-src binary-bootstrap
echo "XBPS_ALLOW_RESTRICTED=yes" >> etc/conf
./xbps-src pkg srcpkgs/discord
xi discord
./xbps-src pkg srcpkgs/steam
xi steam
sudo xbps-install -S nvidia-libs-32bit 
sudo xbps-install -S nethack fortune-mod cowsay
cd ..
echo "[[ "$(tty)" = "/dev/tty1" ]] && fortune | cowsay" >> .bashrc
echo "[[ "$(tty)" != "/dev/tty1" ]] && setxkbmap -layout br -variant abnt2 &" >> .bashrc
echo "You may have to install additional listed libraries by Steam in order for it to properly work. UPDATE the shell script after writting them down."
echo "You will also need to compile Kdenlive and Blender by yourself. Too outdated in xbps for your sane usage."
