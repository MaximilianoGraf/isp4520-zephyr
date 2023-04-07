# isp4520-zephyr
LoRa app demonstration using isp4520 board

## installation steps
1- download and install vscode: https://code.visualstudio.com/

2- download nRF connect plugin

![image](https://user-images.githubusercontent.com/73368714/229951189-e0b1cbb9-cb50-4ceb-b6cb-fd661b8eb3dd.png)

3- follow the instructions:

![image](https://user-images.githubusercontent.com/73368714/229951772-3a5c864e-55aa-4371-8c31-918078bd6e78.png)

4- download nrfConnect for Desktop

![image](https://user-images.githubusercontent.com/73368714/229951933-f755e569-44de-457b-90cc-68fdedb3ba14.png)

5- install toolchain manager

![image](https://user-images.githubusercontent.com/73368714/229954716-b4e4a084-09cb-431b-9c2a-9b7ed3bec6b8.png)

6- select sdk

![image](https://user-images.githubusercontent.com/73368714/229954832-365daf9c-fe7c-40a8-aa1a-c00465b522d5.png)

7- install the suggested nrf plugins

8- finally download and install nrf command line tools deb package

5- clone this repo

6- import project

7- copy the folder isp4520_nrf52832 into toolchain directory, usually $TOOLCHAIN_INSTALLATION_PATH/ncs/$TOOLCHAIN_VERSION/zephyr/boards/arm/

8- edit the build configuration to use the board isp4520_nrf52832

![image](https://user-images.githubusercontent.com/73368714/229959905-415b8304-bb4e-477c-8c84-dc258207b901.png)

9- add the following CMake argument to indicate where the board root files are located

![image](https://user-images.githubusercontent.com/73368714/230666591-2213b613-2018-43f9-81a2-bc30ab9e8deb.png)

10- build hello_isp4520

![image](https://user-images.githubusercontent.com/73368714/229962654-e0b381d4-c14c-4374-9c06-c0885e710e68.png)

11- connect the board

![image](https://user-images.githubusercontent.com/73368714/229963139-a9ac0515-7e2b-4949-8fff-6b6ff01e0f6a.png)

12- download firmware

![image](https://user-images.githubusercontent.com/73368714/230667239-2d01b26e-70df-40c8-82c9-fac305a3fb2d.png)

13- reset or poweroff/on the board
