cmd_/home/pi/device-drivers/native/q2-3/modules.order := {   echo /home/pi/device-drivers/native/q2-3/operator.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/q2-3/modules.order
