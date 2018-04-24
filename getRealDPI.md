
Note: Most of the following contents are from [[1]](https://askubuntu.com/questions/197828/how-to-find-and-change-the-screen-dpi)
with according modifications in terms of my environment and extra information added.

## 1. What's PPI, PPCM, DPI, and DIPs [[2, 3, 4]](https://en.wikipedia.org/wiki/Pixel_density)?

Pixels per inch (**PPI**) or pixels per centimeter (**PPCM**) are measurements of the pixel density (resolution) of monitors. 
It is related to the size of the display in inches and the total number of pixels in the horizontal and vertical directions. 
This measurement is often referred to as dots per inch (**DPI**). 

Distinguish two concepts [[3]](https://en.wikipedia.org/wiki/Dots_per_inch):

* **logical PPI**: The PPI that software claims a screen provides. 
This can be thought of as the PPI provided by a virtual screen created by the operating system.

* **physical PPI**: The PPI that a physical screen actually provides.

Software programs render images to the virtual screen and then the operating system renders the 
virtual screen onto the physical screen through automatic DPI scaling. 
To avoid DPI scaling, programs should be designed to be DPI-aware.

Distinguish another two concepts [[4]](https://msdn.microsoft.com/en-us/library/windows/desktop/ff684173(v=vs.85).aspx): 

* **physical inch**.

* **logical inch**. If the DPI of the monitor is 96, then there are 96 pixels in a logical inch.

The size of a pixel depends on two factors: the display resolution, and the physical size of the monitor. 
Therefore, physical inches are not a useful measure, because there is no fixed relation between physical inches and pixels. 

Therefore, comes the concepts of device-independent pixels (**DIPs**), which is coordinates are measured in units. 
For example, a DIP is defined as 1/96th of a logical inch. 
In Direct2D, all drawing operations are specified in DIPs and then scaled to the current DPI setting
[[4]](https://msdn.microsoft.com/en-us/library/windows/desktop/ff684173(v=vs.85).aspx).

Thus, the effort of this material is to **get** and **fix** the real physical size f a pixel. That is, to get the **actual real physical DPI** 
in the sense of one physical inch, rather than a logical inch.

## 2. My envrionment

* Ubuntu 16.04

* Display monitor: Samsung 28''


## 3. Hardcoded DPI!

* My starting settings:

> $ xdpyinfo | grep dots

resolution:    96x96 dots per inch

> $ xrdb -query | grep dpi

Xft.dpi:	96

> $ xrdb -query | grep DPI /var/log/Xorg.0.log 

[    32.502] (==) NOUVEAU(0): DPI set to (96, 96)

In 16.04 the outputs of all these 3 commands were consistent and were equal to 96, 
which is **hardcoded** and far from the real DPI value.


## 4. Now compute the optimal DPI for the current monitor

* Actual size of the screen can be found by

> $ xrandr | grep -w connected

HDMI-1 connected primary 1920x1080+0+0 (normal left inverted right x axis y axis) 608mm x 345mm

* Divide them by 25.4 to get the size in inches:

23.93700787401574803149 in x 13.58267716535433070866 in

* Lastly divide the actual dots amount (based on your resolution) by the size in inches

X: 1920 / 23.93700787401574803149 dpi = 80.21052631578947368423 dpi ~ 80 dpi

Y: 1080 / 13.58267716535433070866 dpi = 79.51304347826086956522 dpi ~ 80 dpi

So my real dpi is 80.

* **Important**: an automatic real DPI shell script

The real DPI can be obtained automatically by the follwoing shell script.

[getRealDPI.sh](https://github.com/LijunSun90/environmentSetupForLinux/blob/master/getRealDPI.sh)


## 5. Start fixing DPI:

* Create lightdm.conf manually and put it into /etc/lightdm/lightdm.conf.d/ 

The contents of this file are the same:

[SeatDefaults]
xserver-command=X -dpi 80

* Restart your computer or restart X. 

* Test

> $ xrdb -query | grep DPI /var/log/Xorg.0.log

[    27.222] (++) NOUVEAU(0): DPI set to (80, 80)

* Run "Startup Applications", press "Add" button, name it "Fix DPI" and set the command xrandr --dpi 80 in the field. 
Save the changes and re-login. 

* Test

> $ xdpyinfo | grep dots

resolution:    80x80 dots per inch

**Optional:**

* In GNOME3 DPI setting is hardcoded to 96 and cannot be changed directly, but the text can be scaled instead. 
Calculate the desired multiplier: desired_DPI / 96 (in my case 80/96 = .83333333333333333333). Now run the command (or use dconf if you prefer):

> $ gsettings set org.gnome.desktop.interface text-scaling-factor .83333333333333333333

Changes will be applied at once. 

> $ xrdb -query | grep dpi 

Xft.dpi:	80

Scale back if you like:

> $ gsettings set org.gnome.desktop.interface text-scaling-factor 1

Test 

> $ xrdb -query | grep dpi 

Xft.dpi:	96



## 6. References:
[1] https://askubuntu.com/questions/197828/how-to-find-and-change-the-screen-dpi

[2] Wikipedia: Pixel density. [Online] https://en.wikipedia.org/wiki/Pixel_density

[3] Wikipedia: Dots per inch. [Online] https://en.wikipedia.org/wiki/Dots_per_inch

[4] Microsoft: DPI and Device-Independent Pixels. [Online] https://msdn.microsoft.com/en-us/library/windows/desktop/ff684173(v=vs.85).aspx
