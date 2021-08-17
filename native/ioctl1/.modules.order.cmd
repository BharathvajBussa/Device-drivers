cmd_/home/pi/device-drivers/native/ioctl1/modules.order := {   echo /home/pi/device-drivers/native/ioctl1/IOCTL.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/ioctl1/modules.order
