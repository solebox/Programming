Client library for the Google Market APK Expansion files.

downloader_library
A library that works with the google_market_licensing library to download APK Expansion files in a background service.  This library depends on the licensing library, and must be built as a library project.
zip_file
A library that uses multiple zip files as a virtual read-only filesystem with hooks to support APK Expansion lies. This also must be built as an Android library project.
downloader_sample
A sample application that assumes that zip format files have been uploaded as the main/patch file(s) on Android Market.  It downloads these files and then validates that the CRC's for every entry in the zip match.  This application depends on the downloader_library and the zip_file library. Because of dependency issues involving multiple libraries, you may have to do a clean build after creating each project.

See the documentation at http://developer.android.com/guide/market/expansion-files.html

This library requires the licensing library.

See the licensing documentation at http://developer.android.com/guide/publishing/licensing.html
