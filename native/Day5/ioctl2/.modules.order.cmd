cmd_/home/pi/device-drivers/native/ioctl2/modules.order := {   echo /home/pi/device-drivers/native/ioctl2/IOCTL.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/ioctl2/modules.order
