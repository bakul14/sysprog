Конфиг, использованный для сборки настоящего ядра, можно прочитать в файле /boot/config-$(uname -r)

```bash
./install_dependencies.sh
cd linux
make distclean
cp ../old_config .config
make olddefconfig
scripts/config --set-str SYSTEM_TRUSTED_KEYS "" --set-str SYSTEM_REVOCATION_KEYS ""
make -j$(nproc)
sudo make modules_install
sudo make install
echo 'GRUB_TIMEOUT_STYLE=menu' | sudo tee -a /etc/default/grub
echo 'GRUB_TIMEOUT=5' | sudo tee -a /etc/default/grub
echo 'GRUB_TOP_LEVEL="/boot/vmlinux-7.3.0"' | sudo tee -a /etc/default/grub
sudo update-grub
sudo reboot
```
