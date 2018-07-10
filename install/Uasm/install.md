
Copy to an directory example C:\Assembly\Uasm

Add system enviroment variable UASM_PATH C:\Assembly\Uasm

copy BuildCustomizations to:

VS2015 C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\v140\BuildCustomizations

VS2017 C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE\VC\VCTargets\BuildCustomizations

Create an VC project and add by right click project -Buld Dependencies - Build Customization -  check uasm(.targets, .props)