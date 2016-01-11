###MT6582 Kernel-3.4.67 Source for Huawei H30T00

		sudo apt-get install ccache
		sudo gedit ~/.bashrc
Add:

		export USE_CCACHE=1
		export CCACHE_DIR=~/android/.ccache

Build:

		sudo chmod -R 777 * ~/android_kernel_mediatek_h30t00/arm-eabi-4.8
		cd ~/android_kernel_mediatek_h30t00/kernel-3.4
		export ARCH=arm && export ARCH_MTK_PLATFORM=mt6582 && export CROSS_COMPILE=~/android_kernel_mediatek_h30t00/arm-eabi-4.8/bin/arm-eabi- && TARGET_PRODUCT=huawei82_cwet_kk
		./mk r k


* Working
  * Everything

* Added
  * Many cpufreq_governors.
  * Boot with selinux permissive.
