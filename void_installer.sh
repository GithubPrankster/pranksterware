sudo xbps-install -S void-repo-nonfree void-repo-multilib void-repo-multilib-nonfree
sudo xbps-install -Syv
sudo xbps-install -S vim gcc make patch git curl xtools libopenal glm glfw xorg-minimal xorg-fonts fvwm nvidia pcmanfm audacity gimp obs ffmpeg setxkbmap
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
