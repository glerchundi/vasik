#/bin/bash

if [ "$#" -eq 0 ]
then
    echo $0 binfile
    exit 0
else
	OUTPUT=$1
fi

INFOPLIST="<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<!DOCTYPE plist SYSTEM \"file://localhost/System/Library/DTDs/PropertyList.dtd\">
<plist version=\"0.9\">
<dict>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleIdentifier</key>
    <string>org.wxwindows.IDENTIFIER</string>
    <key>CFBundleDevelopmentRegion</key>
    <string>English</string>
    <key>CFBundleExecutable</key>
    <string>EXECUTABLE</string>
    <key>CFBundleIconFile</key>
    <string>wxmac.icns</string>
    <key>CFBundleName</key>
    <string>EXECUTABLE</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleSignature</key>
    <string>????</string>
    <key>CFBundleVersion</key>
    <string>VERSION</string>
    <key>CFBundleShortVersionString</key>
    <string>VERSION</string>
    <key>CFBundleGetInfoString</key>
    <string>EXECUTABLE version VERSION, 2009 Gorka Lertxundi Osa</string>
    <key>CFBundleLongVersionString</key>
    <string>VERSION, (c) 2002 wxWindows</string>
    <key>NSHumanReadableCopyright</key>
    <string>Copyleft 2009 Gorka Lertxundi Osa</string>
    <key>LSRequiresCarbon</key>
        <true/>
    <key>CSResourcesFileMapped</key>
    <true/>
</dict>
</plist>"

echo ""
echo "**********************************"
echo "* Creating application bundle... *"
echo "**********************************"

set -o verbose

mkdir -p $OUTPUT.app/Contents
mkdir -p $OUTPUT.app/Contents/MacOS
mkdir -p $OUTPUT.app/Contents/Resources

INFOPLIST=`echo $INFOPLIST | sed -e "s/IDENTIFIER//g"`
INFOPLIST=`echo $INFOPLIST | sed -e "s/EXECUTABLE/$OUTPUT/g"`
INFOPLIST=`echo $INFOPLIST | sed -e "s/VERSION/0.0.0/g"`

echo $INFOPLIST > $OUTPUT.app/Contents/Info.plist
echo -n "APPL????" > $OUTPUT.app/Contents/PkgInfo

cp $OUTPUT $OUTPUT.app/Contents/MacOS/$OUTPUT
cp libvasik.dylib $OUTPUT.app/Contents/Resources/
cp *.so $OUTPUT.app/Contents/Resources/
cp -fr data $OUTPUT.app/Contents/Resources/

install_name_tool -change libvasik.dylib @executable_path/../Resources/libvasik.dylib $OUTPUT.app/Contents/MacOS/$OUTPUT
