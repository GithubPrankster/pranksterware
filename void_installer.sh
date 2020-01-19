sudo xbps-install -S void-repo-nonfree void-repo-multilib void-repo-multilib-nonfree
sudo xbps-install -Syv
sudo xbps-install -S nano gcc make patch git curl xtools libopenal glm glfw firefox xorg-minimal xorg-fonts icewm nvidia pcmanfm audacity gimp obs ffmpeg setxkbmap menumaker
echo "Cloning void-packages."
git clone https://github.com/void-linux/void-packages.git
cd void-packages
./xbps-src binary-bootstrap
echo "XBPS_ALLOW_RESTRICTED=yes" >> etc/conf
echo "Installing Discord."
./xbps-src pkg srcpkgs/discord
xi discord
echo "Installing Steam"
./xbps-src pkg srcpkgs/steam
xi steam
sudo xbps-install -S nvidia-libs-32bit libdrm-32bit libgcc-32bit libstd++-32bit
echo "Installing fun stuff."
sudo xbps-install -S nethack fortune-mod cowsay
cd ..
echo ". $HOME/.bash_profile" >> .xinitrc
echo "icewm" >> .xinitrc
mmaker IceWM
echo "[[ "$(tty)" = "/dev/tty1" ]] && fortune | cowsay" >> .bashrc
echo "[[ "$(tty)" != "/dev/tty1" ]] && setxkbmap -layout br -variant abnt2 &" >> .bashrc
echo "Use mmaker -h to get the WM you installed up and going with stuff."
echo "You will also need to compile Kdenlive by yourself. Too outdated in xbps for your sane usage."
