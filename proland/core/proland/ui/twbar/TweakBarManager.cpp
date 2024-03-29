/*
 * Proland: a procedural landscape rendering library.
 * Website : http://proland.inrialpes.fr/
 * Copyright (c) 2008-2015 INRIA - LJK (CNRS - Grenoble University)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 * may be used to endorse or promote products derived from this software without 
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 * Proland is distributed under the Berkeley Software Distribution 3 Licence. 
 * For any assistance, feedback and enquiries about training programs, you can check out the 
 * contact page on our website : 
 * http://proland.inrialpes.fr/
 */
/*
 * Main authors: Eric Bruneton, Antoine Begault, Guillaume Piolat.
 */

#include "proland/ui/twbar/TweakBarManager.h"

#include "ork/core/Iterator.h"
#include "ork/resource/ResourceTemplate.h"
#include "ork/render/FrameBuffer.h"
#include "ork/ui/Window.h"

#include "proland/ui/twbar/TweakBarHandler.h"

using namespace ork;

namespace proland
{

static  void ActivateHandlerCallback(const void *value, void *clientData)
{
    TweakBarManager::BarData *b = (TweakBarManager::BarData *)clientData;
    b->setActive(*(bool*) value);
}

static  void GetHandlerStatusCallback(void *value, void *clientData)
{
    TweakBarManager::BarData *b = (TweakBarManager::BarData *)clientData;
    *static_cast<bool*> (value) = b->bar->isActive();
}

TweakBarManager::BarData::BarData(TweakBarManager *owner, ptr<TweakBarHandler> bar, bool exclusive, bool permanent, char k)
{
    this->owner = owner;
    this->bar = bar;
    this->exclusive = exclusive;
    this->permanent = permanent;
    this->k = k;
    assert(!permanent || !exclusive);
}

void TweakBarManager::BarData::setActive(bool active)
{
    if (exclusive && active) {
        owner->resetStates();
    }
    bar->setActive(active);
    owner->initBar();
}

TweakBarManager::TweakBarManager() : EventHandler("TweakBarManager")
{
}

TweakBarManager::TweakBarManager(vector<BarData> bars, bool minimized) : EventHandler("TweakBarManager")
{
    assert(FrameBuffer::getError() == 0);
    TwInit(TW_OPENGL, NULL);
    assert(FrameBuffer::getError() == 0);
    init(bars, minimized);
    assert(FrameBuffer::getError() == 0);
}

void TweakBarManager::init(vector<BarData> bars, bool minimized)
{
    this->bars = bars;
    this->minimized = minimized;
    initialized = false;
    updated = true;
    selectBar = NULL;
}

TweakBarManager::~TweakBarManager()
{
    if (selectBar != NULL) {
        TwDeleteBar(selectBar);
    }
    TwTerminate();
}

void TweakBarManager::initBar()
{
    if (selectBar != NULL) {
        TwRemoveAllVars(selectBar);
    } else {
        selectBar = TwNewBar("SelectHandlersBar");
        TwSetParam(selectBar, NULL, "iconified", TW_PARAM_INT32, 1, &minimized);
    }

    TwSetParam(selectBar, NULL, "label", TW_PARAM_CSTRING, 1, "Toggle Editors");
    TwSetParam(selectBar, NULL, "visible", TW_PARAM_CSTRING, 1, "true");

    bool separator = false;
    char barText[100];
    char barDef[100];
    for (int i = 0; i < (int) bars.size(); i++) {
        BarData *b = &(bars[i]);
        if (b->permanent || b->exclusive) {
            continue;
        }
        sprintf(barText, "%sHandler", b->bar->getName());
        sprintf(barDef, b->k == 0 ? "" : "key='%c'", b->k);

        TwAddVarCB(selectBar, barText, TW_TYPE_BOOL32, ActivateHandlerCallback, GetHandlerStatusCallback, &bars[i], barDef);
        TwSetParam(selectBar, barText, "label", TW_PARAM_CSTRING, 1, b->bar->getName());
        separator = true;
    }

    for (int i = 0; i < (int) bars.size(); i++) {
        BarData *b = &(bars[i]);
        if (b->permanent || !b->exclusive) {
            continue;
        }
        sprintf(barText, "%sHandler", b->bar->getName());
        sprintf(barDef, b->k == 0 ? "" : "key='%c'", b->k);

        TwAddVarCB(selectBar, barText, TW_TYPE_BOOL32, ActivateHandlerCallback, GetHandlerStatusCallback, &bars[i], barDef);
        TwSetParam(selectBar, barText, "label", TW_PARAM_CSTRING, 1, b->bar->getName());
        separator = true;
    }
    if (separator) {
        TwAddSeparator(selectBar, NULL, NULL);
    }

    for (int i = 0;i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bars[i].bar->updateBar(selectBar);
        }
    }
    initialized = true;
    updated = false;
}

ptr<EventHandler> TweakBarManager::getNext()
{
    return next;
}

void TweakBarManager::setNext(ptr<EventHandler> next)
{
    this->next = next;
}

void TweakBarManager::redisplay(double t, double dt)
{
    if (next != NULL) {
        next->redisplay(t, dt);
    }
    if (!initialized || updated) {
        initBar();
    }

    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bars[i].bar->redisplay(t, dt, needUpdate);
            updated |= needUpdate;
        }
    }
}

void TweakBarManager::reshape(int x, int y)
{
    TwWindowSize(x, y);
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bars[i].bar->reshape(x, y, needUpdate);
            updated |= needUpdate;
        }
    }
    if (next != NULL) {
        next->reshape(x, y);
    }
}

void TweakBarManager::idle(bool damaged)
{
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bars[i].bar->idle(damaged, needUpdate);
            updated |= needUpdate;
        }
    }
    if (next != NULL) {
        next->idle(damaged);
    }
}

bool TweakBarManager::mouseClick(button b, state s, modifier m, int x, int y)
{
    if (TwGetBarCount() >= 1) {
        TwMouseAction action = s == DOWN ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
        switch (b) {
            case LEFT_BUTTON:
                if (TwMouseButton(action, TW_MOUSE_LEFT) == 1) {
                    return true;
                }
                break;
            case RIGHT_BUTTON:
                if (TwMouseButton(action, TW_MOUSE_RIGHT) == 1) {
                    return true;
                }
                break;
            case MIDDLE_BUTTON:
                if (TwMouseButton(action, TW_MOUSE_MIDDLE) == 1) {
                    return true;
                }
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->mouseClick(b, s, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->mouseClick(b, s, m, x, y);
}

bool TweakBarManager::mouseWheel(wheel b, modifier m, int x, int y)
{
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->mouseWheel(b, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->mouseWheel(b, m, x, y);
}

bool TweakBarManager::mouseMotion(int x, int y)
{
    if (TwGetBarCount() >= 1) {
        if (TwMouseMotion(x, y) == 1) {
            return true;
        }
    }
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->mouseMotion(x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->mouseMotion(x, y);
}

bool TweakBarManager::mousePassiveMotion(int x, int y)
{
    if (TwGetBarCount() >= 1) {
        if (TwMouseMotion(x, y) == 1) {
            return true;
        }
    }
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->mousePassiveMotion(x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->mousePassiveMotion(x, y);
}

bool TweakBarManager::keyTyped(unsigned char c, modifier m, int x, int y)
{
    if (TwGetBarCount() >= 1) {
        int kmod = 0;
        if (m & SHIFT) {
            kmod |= TW_KMOD_SHIFT;
        }
        if (m & CTRL) {
            kmod |= TW_KMOD_CTRL;
        }
        if (m & ALT) {
            kmod |= TW_KMOD_ALT;
        }

        if ((kmod & TW_KMOD_CTRL) && (c > 0 && c < 27)) {  // CTRL special case
            c += 'a' - 1;
        }

        if (TwKeyPressed((int) c, kmod) == 1) {
            return true;
        }
    }
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->keyTyped(c, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->keyTyped(c, m, x, y);
}

bool TweakBarManager::keyReleased(unsigned char c, modifier m, int x, int y)
{
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->keyReleased(c, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->keyReleased(c, m, x, y);
}

bool TweakBarManager::specialKey(key  k, modifier m, int x, int y)
{
    if (TwGetBarCount() >= 1) {

        int kmod = 0;
        if (m & SHIFT) {
            kmod |= TW_KMOD_SHIFT;
        }
        if (m & CTRL) {
            kmod |= TW_KMOD_CTRL;
        }
        if (m & ALT) {
            kmod |= TW_KMOD_ALT;
        }

        int key = 0;
        switch (k) {
        case KEY_F1:
            key = TW_KEY_F1;
            break;
        case KEY_F2:
            key = TW_KEY_F2;
            break;
        case KEY_F3:
            key = TW_KEY_F3;
            break;
        case KEY_F4:
            key = TW_KEY_F4;
            break;
        case KEY_F5:
            key = TW_KEY_F5;
            break;
        case KEY_F6:
            key = TW_KEY_F6;
            break;
        case KEY_F7:
            key = TW_KEY_F7;
            break;
        case KEY_F8:
            key = TW_KEY_F8;
            break;
        case KEY_F9:
            key = TW_KEY_F9;
            break;
        case KEY_F10:
            key = TW_KEY_F10;
            break;
        case KEY_F11:
            key = TW_KEY_F11;
            break;
        case KEY_F12:
            key = TW_KEY_F12;
            break;
        case KEY_LEFT:
            key = TW_KEY_LEFT;
            break;
        case KEY_UP:
            key = TW_KEY_UP;
            break;
        case KEY_RIGHT:
            key = TW_KEY_RIGHT;
            break;
        case KEY_DOWN:
            key = TW_KEY_DOWN;
            break;
        case KEY_PAGE_UP:
            key = TW_KEY_PAGE_UP;
            break;
        case KEY_PAGE_DOWN:
            key = TW_KEY_PAGE_DOWN;
            break;
        case KEY_HOME:
            key = TW_KEY_HOME;
            break;
        case KEY_END:
            key = TW_KEY_END;
            break;
        case KEY_INSERT:
            key = TW_KEY_INSERT;
            break;
        }

        if (key > 0 && key < TW_KEY_LAST) {
            if (TwKeyPressed(key, kmod) == 1) {
                return true;
            }
        }
    }
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->specialKey(k, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->specialKey(k, m, x, y);
}

bool TweakBarManager::specialKeyReleased(key  k, modifier m, int x, int y)
{
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].bar->isActive()) {
            bool needUpdate = false;
            bool handled = bars[i].bar->specialKeyReleased(k, m, x, y, needUpdate);
            updated |= needUpdate;
            if (handled) {
                return true;
            }
        }
    }
    return next != NULL && next->specialKeyReleased(k, m, x, y);
}

void TweakBarManager::resetStates()
{
    for (int i = 0; i < (int) bars.size(); i++) {
        if (bars[i].exclusive) {
            bars[i].bar->setActive(false);
        }
    }
}

void TweakBarManager::swap(ptr<TweakBarManager> t)
{
    std::swap(selectBar, t->selectBar);
    std::swap(bars, t->bars);
    std::swap(next, t->next);
    std::swap(minimized, t->minimized);
    std::swap(initialized, t->initialized);
    std::swap(updated, t->updated);
}

class TweakBarManagerResource : public ResourceTemplate<0, TweakBarManager>
{
public:
    TweakBarManagerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<0, TweakBarManager> (manager, name, desc)
    {
        TwInit(TW_OPENGL, NULL);

        e = e == NULL ? desc->descriptor : e;

        checkParameters(desc, e, "name,minimized,next,");

        vector<BarData> bars;

        bool minimized = true;
        if (e->Attribute("minimized") != NULL) {
            minimized = strcmp(e->Attribute("minimized"), "true") == 0;
        }

        const TiXmlNode *n = e->FirstChild();
        while (n != NULL) {
            const TiXmlElement *f = n->ToElement();
            if (f == NULL) {
                n = n->NextSibling();
                continue;
            }
            if (strcmp(f->Value(), "editor") == 0) {
                checkParameters(desc, f, "id,bar,exclusive,permanent,key,");
                string id = getParameter(desc, f, "id");

                ptr<TweakBarHandler> h = manager->loadResource(getParameter(desc, f, "bar")).cast<TweakBarHandler>();
                bool exclusive = true;
                bool permanent = false;
                char k = 0;
                if (f->Attribute("exclusive") != NULL) {
                    exclusive = strcmp(f->Attribute("exclusive"), "true") == 0;
                }
                if (f->Attribute("permanent") != NULL) {
                    permanent = strcmp(f->Attribute("permanent"), "true") == 0;
                }
                if (f->Attribute("key") != NULL) {
                    k = f->Attribute("key")[0];
                }
                bars.push_back(BarData(this, h, exclusive, permanent, k));
            }
            n = n->NextSibling();
        }

        if (e->Attribute("next") != NULL) {
            setNext(manager->loadResource(getParameter(desc, e, "next")).cast<EventHandler>());
        }

        init(bars, minimized);
    }
};

extern const char tweakBarManager[] = "tweakBarManager";

static ResourceFactory::Type<tweakBarManager, TweakBarManagerResource> TweakBarManagerType;

}
