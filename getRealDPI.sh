
# Get the real physical DPI (dots per inch) for the currrent monitor
# Author: Lijun Sun
# Date: 2018.04.13

echo "The default resolution value from the operating system is:

    $(xdpyinfo | grep dots)\n\n"

resolution=$(xrandr | grep -w connected | grep -o -E '[0-9]*x[0-9]*\+[0-9]*\+[0-9]*' | grep -o -E '[0-9]*x[0-9]*')
resolutionX=$(echo $resolution | cut -d"x" -f1)
resolutionY=$(echo $resolution | cut -d"x" -f2)
echo "The resolution of the current monitor is: 

    $resolutionX pixels x $resolutionY pixels. \n\n"

physicalSZ_mm=$(xrandr | grep -w connected | grep -o -E '[0-9]*mm x [0-9]*mm' | grep -o -E '[0-9]+')
physicalX_mm=$(echo $physicalSZ_mm | cut -d " " -f1)
physicalY_mm=$(echo $physicalSZ_mm | cut -d " " -f2)
echo "The physical size of the current monitor is: 

    $physicalX_mm mm x $physicalY_mm mm.\n\n"

physicalX_inch=$(echo "$physicalX_mm/25.4" | bc -l)
physicalY_inch=$(echo "$physicalY_mm/25.4" | bc -l)

dpiX=$(echo "$resolutionX/$physicalX_inch" | bc -l)
dpiY=$(echo "$resolutionX/$physicalX_inch" | bc -l)

# Round the result to the nearest integer.
echo "The REAL ACTUAL DPI (dots per inch) of the current monitor is: 

    $(printf '%.*f\n' 0 $dpiX) pixels/inch x $(printf '%.*f\n' 0 $dpiY) pixels/inch \n\n"
