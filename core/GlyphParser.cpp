// GlyphParser.cpp
//
// Created by Zhang Yungui on 14-8-15.
// Copyright (c) 2014, LGPL 2.1 license, https://github.com/touchvg/DemoImport

#include "GlyphParser.h"
#include "mgjsonstorage.h"
#include "mgstorage.h"
#include "mgview.h"
#include "mgbasicsps.h"
#include "mgspfactory.h"

static void parseOutline(MgView* view, MgStorage* s)
{
    if (s->readNode("R", -1, false)) {
        MgShape *sp = view->getShapeFactory()->createShape(MgPathShape::Type());
        MgPath& path = ((MgPathShape*)sp->shape())->path();
        
        for (int j = 0; s->readNode(NULL, j, false); j++) {
            int t = s->readInt("t", -100);
            float x = s->readFloat("x", -100);
            float y = s->readFloat("y", -100);
            float x1 = s->readFloat("cx1", -100);
            float y1 = s->readFloat("cy1", -100);
            float x2 = s->readFloat("cx2", -100);
            float y2 = s->readFloat("cy2", -100);
            
            s->readNode(NULL, j, true);
            if (t == 0) {
                path.moveTo(Point2d(x, y));
            }
            else if (t == 1) {
                path.lineTo(Point2d(x, y));
            }
            else if (x1 >= 0) {
                path.bezierTo(Point2d(x1, y1), Point2d(x2, y2), Point2d(x, y));
            }
        }
        s->readNode("R", -1, true);
        
        path.closeFigure();
        
        //sp->shape()->setFlag(kMgLocked, true);
        sp->shape()->setFlag(kMgNoClone, true);
        sp->shape()->setFlag(kMgNoAction, true);
        sp->shape()->setFlag(kMgNoSnap, true);
        
        GiContext ctx(sp->context());
        ctx.setLineWidth(0, false);
        ctx.setLineColor(100, 100, 100);
        ctx.setFillColor(255, 255, 255, 240);
        sp->setContext(ctx);
        
        view->shapes()->addShapeDirect(sp);
    }
}

static void parseTrace(MgView* view, MgStorage* s)
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

bool GlyphParser::loadFile(const long cmdview, const char* filename)
{
    MgView* view = MgView::fromHandle(cmdview);
    FILE *fp = mgopenfile(filename, "rt");
    
    if (!fp) {
        return false;
    }
    
    MgJsonStorage js;
    MgStorage* s = js.storageForRead(fp);
    
    fclose(fp);
    if (js.getParseError())
        return false;
    
    s->readNode("", -1, false);
    
    char name[7];
    int size;
    s->readString("unicode", name, sizeof(name));
    size = s->readInt("size", 0);
    
    if (s->readNode("points", -1, false)) {
        for (int i = 0; s->readNode(NULL, i, false); i++) {
            parseOutline(view, s);
            parseTrace(view, s);
            s->readNode(NULL, i, true);
        }
        s->readNode("points", -1, true);
    }
    s->readNode("", -1, true);
    
    view->modelTransform() = Matrix2d::scaling(0.5f, -0.5f);
    view->xform()->setModelTransform(view->modelTransform());
    view->regenAll(true);
    
    return size > 0;
}
