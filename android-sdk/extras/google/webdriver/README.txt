WebDriver for Android allows you to write test for your Android Web Application (see sample code).

WebDriver is an Open Source project hosted at http://selenium.googlecode.com.
This jar was created at revision r14435.

The javadoc can be found here: http://selenium.googlecode.com/svn/trunk/docs/api/java/index.html

Note: The android_webdriver_library.jar uses the guava libraries that can be downloaded here:
http://code.google.com/p/guava-libraries/

For Android WebDriver questions, subscribe to webdriver@googlegroups.com. For announcements 
keep an eye on the Selenium blog at http://seleniumhq.wordpress.com/.

Relevant links:
http://android-developers.blogspot.com/2011/10/introducing-android-webdriver.html


################################################################################################
Command line instructions:
$ unzip WebDriver.zip

# Build and install SimpleApp
$ cd SimpleApp
$ android update project -p ./
$ ant debug
$ adb install -r bin/SimpleAppActivity-debug.apk

# Build and install TestAnAndroidWebApp
$ cd TestAnAndroidWebApp
$ android update test-project -m ../SimpleApp/ -p ./
$ ant debug;
$ adb install -r bin/SimpleAppActivityTest-debug.apk;

# Run the test
$ adb shell am instrument -w simple.app.test/android.test.InstrumentationTestRunner

Eclipse instructions:
$ unzip WebDriver.zip

Import the projects in eclipse: File -> Import -> General -> Existing Projects into
Workspace. Then select the root directory WebDriver, which contains both
SimpleApp and TestAnAndroidWebApp. Note that those are Android projects, and require the
Android Eclipse ADT plugin to be installed.

Launch the test: Right click on TestAnAndroidWebApp -> Run As -> Android Junit Test.

If you would like to see the JavaDoc in your IDE, you can link the source jar provided.
In Eclipse, right click on the android_webdriver_library.jar -> Properties ->
Java Source Attachment and select the android_webdriver_library-srcs.jar.
################################################################################################

