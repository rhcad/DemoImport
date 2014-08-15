# DemoImport

DemoImport is an example project which can import other vector format files.

Shape importing example in C++: [GlyphParser.cpp](core/GlyphParser.cpp)

```cpp
void parseTrace(MgView* view, MgStorage* s)
{
    if (s->readNode("T", -1, false)) {
        MgShape *sp = view->getShapeFactory()->createShape(MgLines::Type());
        MgLines *lines = (MgLines*)sp->shape();
        
        for (int j = 0; s->readNode(NULL, j, false); j++) {
            lines->addPoint(Point2d(s->readFloat("x", 0), s->readFloat("y", 0)));
            s->readNode(NULL, j, true);
        }
        s->readNode("R", -1, true);
        
        view->shapes()->addShapeDirect(sp);
    }
}
```

## Build for iOS

### Compile with CocoaPods

1. Cd the 'ios' folder of this project, then type `pod install` or `pod update --no-repo-update`.

2. Open `ios/DemoImport.xcworkspace` in Xcode and run the `DemoImport` demo app.

### Compile without CocoaPods

Alternatively, you can build as one of the following methods:

1. Cd the 'ios' folder of this project and type `./build.sh` or `./build.sh -arch arm64` to checkout and build libraries needed.

2. Open `ios/DemoImport.xcworkspace` in Xcode, then run the `DemoImport` demo app.

## Build for Android

Import the `android/DemoImport` project, then run the `DemoImport` demo app.

## License

This is an open source LGPL 2.1 licensed project based on TouchVG project.

Contributors and sponsors are welcome. You may commit issues or pull requests on this Github site.
