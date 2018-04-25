
## 1. What's the **optical format**?

An intuition sense of the **optical format**: 1/4'', 1/3'', 1/2'', 1/1.8'', 2/3'', etc. 

The **optical format** is one of the **image sensor format**, which is the measurement of the size of the image sensor 
in inches [[1]](https://en.wikipedia.org/wiki/Image_sensor_format), and dates back to a set of standard sizes given to 
TV camera tubes in the 50's [[2]](https://www.dpreview.com/articles/8095816568/sensorsizes).

## 2. What's the actual size of the image sensor [[2]](https://www.dpreview.com/articles/8095816568/sensorsizes)?

However, note that, the size designation does not define the diagonal of the **sensor area** but rather the **outer diameter** 
of the long glass envelope of the tube. 

Engineers soon discovered that for various reasons the usable area of this imaging plane was approximately two thirds of 
the designated size. 

We know that **1 inch = 25.4 mm**. If the usable area is two thirds of the designated size, then the usable size will be
25.4 mm * 2 / 3 = 16.93 mm. I think this is why it is said **1 inch = 16 mm** in this format, which is also an 
approximation I guess.

There appears to be **no** specific mathematical relationship between the diameter of the imaging circle and the sensor size, 
although it is always **roughly** two thirds.



For example, (1inch = 25.4mm), 

* for 1/2.7'', 25.4 / 2.7 / 6.59 = 1.4275;

* for 1/1.8'', 25.4 / 1.8 /8.93 = 1.58;

* for 2/3'', 25.4 * 2 / 3 /11 = 1.539.


Therefore, due to this absense of specific mathematical formula and the roughly approximation,
and due to inch-based sensor formats being not standardized, their exact dimensions may vary
[[1]](https://en.wikipedia.org/wiki/Image_sensor_format).
So, when the optical format is encountered, it is not wise to compute the size according to the formula
[[3]](https://en.wikipedia.org/wiki/Optical_format). 
Instead, look up the specifications in the sheet or online, for example, 
[[1]](https://en.wikipedia.org/wiki/Image_sensor_format).
So, for example, we have the following technical specifications [[2]](https://www.dpreview.com/articles/8095816568/sensorsizes):


|      |              |           | Sensor (mm) | | |
| ---- | ------------ | --------- | -------- | ----- | ------ |
| Type | Aspect Ratio |	Dia. (mm) |	Diagonal | Width |	Height |
| 1.8" |	4:3          |	14.111	   |  8.933   | 7.176 |	5.319  |



## 3. What's the physical size of a pixel in the image sensor?

If the resolution the image sensor of 1/1.8'' is 2048 x 1536, then it seems reasonable to calculate the pixel size:

7.716 mm / 2048 pixles = 3.504 um/pixel (**Wrong!**),

5.319 mm / 1536 pixles = 3.46 um/pixel (**Wrong!**),

which is **Wrong!** 

In fact, there is another thing, the **sensor active area** !

### 3.1 What's **Active area** [[4]](http://cctvcad.com/videocad_help/index.html?prim_sensor_size.htm)?

**Active area** of the sensor implies an area of the sensor on which image is formed, which may be smaller than 
equal to the image sensor.
Active area size depends on the aspect ratio of the sensor and aspect ratio of the output image of the camera. The aspect
ratio of the output image is typically, for example, 16:9 or 4:3.
Therefore, active area can differ in different modes of operation of the same camera.

For example, the specification details of the Sony IMX252LQR [[5]](https://machinevisionstore.com/Catalog/Details/1667) is,

  * Sensor Resolution:	2048 (h) x 1536 (v) pixels
  
  * Pixel Size:	3.45 µm
  
  * Sensor Size:	8.83 mm
  
  * Sensor Active Area:	7.0656 (h) x 5.2992 (v) mm
  
  * Technology:	CMOS Color Progressive Scan

so, we can get

  * 7.0656 mm / 2048 = 3.45 um
  
  * 5.2992 mm / 1536 = 3.45 um
  
 **Therefore, the pixel size is computed from the sensor active area and the sensor resolution.**
 
 So, the next question is: what's the relationship between sensor size and sensor active area?

The tutorials [here](https://www.edmundoptics.com/resources/application-notes/imaging/resolution/)
may be one of the good start.

## 4. An example

 (1) EQUIPMENT: SONY FDR-AX100E Camcorder
 
 (2) SENSOR: 
 
 * SENSOR TYPE: 1.0-type (13.2mm x 8.8mm) back-illuminated Exmor R CMOS sensor
 
 * EFFECTIVE PIXELS (VIDEO): Approx.14.2M pixels(16:9)
 
 * EFFECTIVE PIXELS (STILL IMAGE): Approx.14.2M pixels(16:9)/Approx.10.6M pixels(4:3)
 
 The photo recording pixels and the aspect ratio [[8]](https://www.sony.co.uk/electronics/support/res/manuals/Z013/Z013087111.PDF):
 
 Photo recording mode, Dual Capture:

 * 5,968 × 3,352 = 20,004,736 dots/16:9
 
 * 4,464 × 3,352 = 14,963,328 dots/4:3 (*)
 
 * 5,024 × 2,824 = 14,187,776 dots/16:9 
  
 * 3,760 × 2,824 = 10,618,240 dots/4:3 (*)
 
 * 1,920 × 1,080 = 2,073,600 dots/16:9
 
 * 640 × 480 = 307,200 dots/4:3 (*)
 
 *Not available for Dual Capture
 
 Capturing a photo from a movie (models with the USB IN/OUT jacks) :
 
 * 1,920 × 1,080 = 2,073,600 dots/16:9
 
 (3) LENS:
 
 * APERTURE: F2.8-F4.5
 
 * FOCAL DISTANCE: f=9.3-111.6mm
  
 * FOCAL LENGTH (35 MM EQUIVALENT) (VIDEO): f=29.0-348.0mm(16:9)
  
 * FOCAL LENGTH (35 MM EQUIVALENT) (STILL IMAGE): f=29.0-348.0mm(16:9), f=35.5-426.0mm(4:3)
 
 Therefore,
 
 (4) PIXEL SIZE:
 
 * EFFECTIVE PIXELS (STILL IMAGE): 
 
 13.2 mm / (5024 pixels) = 2.627 um (16:9); 
 
 13.2 mm / (4464 pixels) = 2.957 um (16:9)
 
 13.2 mm / (1920 pixels) = 6.875 um (16:9)
 
 13.2 mm / (640 pixels) = 20.625 um (4:3)
 
 (5) FOCAL LENGHT IN PIXELS:
 
 * STILL IMAGE: 
 
 (16:9) 11039.208, 9807.237, 4218.18 ~  132470.5, 117686.84, 50618.18 pixels
 
 (4:3) 55.46875 ~ 665.625 pixels
 
 
 
 
 


## Reference:

[1] Image sensor format. [Online] https://en.wikipedia.org/wiki/Image_sensor_format

[2] Make (some) sense out of sensor size. [Online] https://www.dpreview.com/articles/8095816568/sensorsizes

[3] Optical format. [Online] https://en.wikipedia.org/wiki/Optical_format

[4] Stanislav Utochkin. "Specifying active area size of the image sensor". Retrieved May 21, 2015. 
[Online] http://cctvcad.com/videocad_help/index.html?prim_sensor_size.htm

[5] Sony IMX252LQR. [Online] https://machinevisionstore.com/Catalog/Details/1667

[6] Resolution. [Online] https://www.edmundoptics.com/resources/application-notes/imaging/resolution/

[7] SONY FDR-AX100E. [Online] https://www.sony.co.uk/electronics/handycam-camcorders/fdr-ax100e/specifications#specifications

[8] Help Guide. [Online] https://www.sony.co.uk/electronics/support/res/manuals/Z013/Z013087111.PDF



