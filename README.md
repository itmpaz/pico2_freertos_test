# Pico 2 FreeRTOS

RP2350 FreeRTOS port
```
git submodule add https://github.com/raspberrypi/FreeRTOS-Kernel.git FreeRTOS-Kernel
git submodule update --init
cp FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ/FreeRTOS_Kernel_import.cmake .
```


[Video](https://youtu.be/vbwfGcv84DM)

[FreeRTOS](https://www.freertos.org/)

[Github](https://github.com/raspberrypi/FreeRTOS-Kernel)

## Task priorites

[Documentaion](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/03-Task-priorities)

[Code](https://github.com/itmpaz/pico2_freertos_test/raw/refs/heads/task_priorities/pico2_freertos_test.c)

## Queues

[Documentation](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues-mutexes-and-semaphores/01-Queues)

[Code](https://github.com/itmpaz/pico2_freertos_test/raw/refs/heads/queue/pico2_freertos_test.c)


## Semaphores

[Documentation](https://www.freertos.org/Documentation/02-Kernel/04-API-references/10-Semaphore-and-Mutexes/00-Semaphores)

[Code](https://github.com/itmpaz/pico2_freertos_test/raw/refs/heads/semaphore/pico2_freertos_test.c)




