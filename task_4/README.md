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
sudo reboot
```
