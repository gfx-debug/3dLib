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

#include "proland/ui/twbar/TweakRivers.h"

#include "ork/resource/ResourceTemplate.h"

using namespace ork;

namespace proland
{

// Particle Radius
static  void SetRadiusCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask*>(clientData)->setParticleRadius(*static_cast<const float *>(value));

}

static  void GetRadiusCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<const DrawRiversTask*>(clientData)->getParticleRadius();
}

//// Max amount of particles
//static TW_CALL void SetMaxPCallback(const void *value, void *clientData)
//{
//  static_cast<ParticleProducer *>(clientData)->getStorage()->setMaxParticles(*static_cast<const int*>(value));
//}
//static TW_CALL void GetMaxPCallback(void *value, void *clientData)
//{
//  *static_cast<int *>(value) = static_cast<const ParticleManager *>(clientData)->getMaxParticles();
//}

// Max particle age
static  void SetMaxAgeCallback(const void *value, void *clientData)
{
    static_cast<LifeCycleParticleLayer *>(clientData)->setActiveDelay(*static_cast<const float *>(value) * 1000000.f);
}

static  void GetMaxAgeCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<const LifeCycleParticleLayer *>(clientData)->getActiveDelay() / 1000000.f;
}

// Particle Fading in Time
static  void SetFadeInCallback(const void *value, void *clientData)
{
    static_cast<LifeCycleParticleLayer *>(clientData)->setFadeInDelay(*static_cast<const float *>(value) * 1000000.f);
}

static  void GetFadeInCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<const LifeCycleParticleLayer *>(clientData)->getFadeInDelay() / 1000000.f;
}

// Particle Fading out Time
static  void SetFadeOutCallback(const void *value, void *clientData)
{
    static_cast<LifeCycleParticleLayer *>(clientData)->setFadeOutDelay(*static_cast<const float *>(value) * 1000000.f);
}

static  void GetFadeOutCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<const LifeCycleParticleLayer*>(clientData)->getFadeOutDelay() / 1000000.f;
}

// Particle Fading in Time
static  void SetFlowSpeedCallback(const void *value, void *clientData)
{
    static_cast<WorldParticleLayer *>(clientData)->setSpeedFactor(*static_cast<const float *>(value));
}

static  void GetFlowSpeedCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<const WorldParticleLayer *>(clientData)->getSpeedFactor();
}

// Particle Fading in Time
static  void SetPausedCallback(const void *value, void *clientData)
{
    static_cast<WorldParticleLayer *>(clientData)->setPaused(*static_cast<const bool *>(value));
}

static  void GetPausedCallback(void *value, void *clientData)
{
    *static_cast<bool *>(value) = static_cast<const WorldParticleLayer *>(clientData)->isPaused();
}

// FlowData slip parameter
static  void SetSlipCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setSlipParameter(-1, *static_cast<const float*>(value));
}

static  void GetSlipCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getSlipParameter(-1);
}

// FlowData potential delta parameter
static  void SetPotentialDeltaCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setPotentialDelta(-1, *static_cast<const float*>(value));
}

static  void GetPotentialDeltaCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getPotentialDelta(-1);
}

static  void SetTimeStepCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setTimeStep(*static_cast<const float*>(value));
}

static  void GetTimeStepCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getTimeStep();
}

static  void SetMeshDisplayTypeCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setMeshDisplayType(*static_cast<const DrawRiversTask::MeshDisplayType*>(value));
}

static  void GetMeshDisplayTypeCallback(void *value, void *clientData)
{
    *static_cast<DrawRiversTask::MeshDisplayType*>(value) = static_cast<DrawRiversTask *>(clientData)->getMeshDisplayType();
}

static  void SetDisplayGridCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->displayGrid(*static_cast<const bool*>(value));
}

static  void GetDisplayGridCallback(void *value, void *clientData)
{
    *static_cast<bool *>(value) = static_cast<DrawRiversTask *>(clientData)->displayGrid();
}

static  void SetDisplayParticlesCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->displayParticles(*static_cast<const bool*>(value));
}

static  void GetdisplayParticlesCallback(void *value, void *clientData)
{
    *static_cast<bool *>(value) = static_cast<DrawRiversTask *>(clientData)->displayParticles();
}

static  void SetDisplayVelocitiesCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->displayVelocities(*static_cast<const bool*>(value));
}

static  void GetDisplayVelocitiesCallback(void *value, void *clientData)
{
    *static_cast<bool *>(value) = static_cast<DrawRiversTask *>(clientData)->displayVelocities();
}

static  void SetDisplaySunEffectsCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->displaySunEffects(*static_cast<const bool*>(value));
}

static  void GetDisplaySunEffectsCallback(void *value, void *clientData)
{
    *static_cast<bool *>(value) = static_cast<DrawRiversTask *>(clientData)->displaySunEffects();
}

static  void SetWaveSlopeCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setWaveSlopeFactor(*static_cast<const float*>(value));
}

static  void GetWaveSlopeCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getWaveSlopeFactor();
}

static  void SetRiverDepthCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setRiverDepth(*static_cast<const float*>(value));
}

static  void GetRiverDepthCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getRiverDepth();
}

static  void SetWaveLengthCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setWaveLength(*static_cast<const float*>(value));
}

static  void GetWaveLengthCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getWaveLength();
}

static  void SetBedLengthCallback(const void *value, void *clientData)
{
    static_cast<DrawRiversTask *>(clientData)->setBedLength(*static_cast<const float*>(value));
}

static  void GetBedLengthCallback(void *value, void *clientData)
{
    *static_cast<float *>(value) = static_cast<DrawRiversTask *>(clientData)->getBedLength();
}

void  ClearParticlesCallback(void *clientData)
{
    ((ParticleStorage*) clientData)->clear();
}

TweakRivers::TweakRivers() : TweakBarHandler()
{
}

TweakRivers::TweakRivers(ptr<DrawRiversTask> drawer, bool active)
{
    init(drawer, active);
}

TweakRivers::~TweakRivers()
{
    if (barStates != NULL) {
        delete barStates;
    }
}

void TweakRivers::init(ptr<DrawRiversTask> drawer, bool active)
{
    TweakBarHandler::init("River Editor", NULL, active);
    this->drawer = drawer;
    this->barStates = new int[4];
    for (int i = 0; i < 4; i++) {
        barStates[i] = true;
    }
    currentBar = NULL;
}

void TweakRivers::redisplay(double t, double dt, bool &needUpdate)
{
    if (currentBar != NULL) {
        TwGetParam(currentBar, "Flow", "opened", TW_PARAM_INT32, 1, &(barStates[0]));
        TwGetParam(currentBar, "Display", "opened", TW_PARAM_INT32, 1, &(barStates[1]));
        TwGetParam(currentBar, "Other", "opened", TW_PARAM_INT32, 1, &(barStates[2]));
        TwGetParam(currentBar, "riverManager", "opened", TW_PARAM_INT32, 1, &(barStates[3]));
    }
    needUpdate = false;
}

void TweakRivers::updateBar(TwBar *bar)
{
    if (drawer == NULL) {
        return;
    }
    LifeCycleParticleLayer *lifeLayer = drawer->getParticles()->getLayer<LifeCycleParticleLayer>();
    WorldParticleLayer *worldLayer = drawer->getParticles()->getLayer<WorldParticleLayer>();

    TwAddVarCB(bar, "pauseFlow", TW_TYPE_BOOL8, SetPausedCallback, GetPausedCallback, worldLayer, " group=Flow label='Update Particles' help='Activate/Deactivate the flow' false='True' true='False' ");
    TwAddVarCB(bar, "timeStep", TW_TYPE_FLOAT, SetTimeStepCallback, GetTimeStepCallback, drawer.get(), " group=Flow label='Time Step' help='Number of Time Steps between each frame' step=0.01 ");
    TwAddVarCB(bar, "flowSpeed", TW_TYPE_FLOAT, SetFlowSpeedCallback, GetFlowSpeedCallback, worldLayer, " group=Flow label='Flow Speed' help='Flow Speed' step=0.01 ");
    TwAddButton(bar, "Clear", ClearParticlesCallback, drawer->getParticles()->getStorage().get(), "group='Flow'");

    TwType twMeshDisplayType = TwDefineEnum("MeshDisplayType", NULL, 0);
    TwAddVarCB(bar, "displayMesh", twMeshDisplayType, SetMeshDisplayTypeCallback, GetMeshDisplayTypeCallback, drawer.get(), "group=Display label='Display Mode' enum='0 {Hidden}, 1 {Particle Coverage}, 5 {Advected}, 6 {Pre-Advected}, 10 {Non Advected} ' ");
    TwAddVarCB(bar, "displayGrid", TW_TYPE_BOOL8, SetDisplayGridCallback, GetDisplayGridCallback, drawer.get(), "group=Display label='Display Grid' ");
    TwAddVarCB(bar, "displayParticles", TW_TYPE_BOOL8, SetDisplayParticlesCallback, GetdisplayParticlesCallback, drawer.get(), "group=Display label='Display Particles' ");
    TwAddVarCB(bar, "displayVelocities", TW_TYPE_BOOL8, SetDisplayVelocitiesCallback, GetDisplayVelocitiesCallback, drawer.get(), "group=Display label='Display Velocities' ");
    TwAddVarCB(bar, "displaySun", TW_TYPE_BOOL8, SetDisplaySunEffectsCallback, GetDisplaySunEffectsCallback, drawer.get(), "group=Display label='Display Sun Effects' ");
    TwAddVarCB(bar, "waveSlope", TW_TYPE_FLOAT, SetWaveSlopeCallback, GetWaveSlopeCallback, drawer.get(), "group=Display label='Wave slope factor' ");
    TwAddVarCB(bar, "waveLength", TW_TYPE_FLOAT, SetWaveLengthCallback, GetWaveLengthCallback, drawer.get(), "group=Display label='Wave length factor' ");
    TwAddVarCB(bar, "riverDepth", TW_TYPE_FLOAT, SetRiverDepthCallback, GetRiverDepthCallback, drawer.get(), "group=Display label='River Depth' min='1' step='0.1' ");
    TwAddVarCB(bar, "bedLength", TW_TYPE_FLOAT, SetBedLengthCallback, GetBedLengthCallback, drawer.get(), "group=Display label='Bed texture length' min='0.001' step='0.001'");

    TwAddVarCB(bar, "fadeInTime", TW_TYPE_FLOAT, SetFadeInCallback, GetFadeInCallback, lifeLayer, "group=Other label='Fading in Time' step=0.1 ");
    TwAddVarCB(bar, "fadeOutTime", TW_TYPE_FLOAT, SetFadeOutCallback, GetFadeOutCallback, lifeLayer, "group=Other label='Fading Out Time' step=0.1 ");
    TwAddVarCB(bar, "maxAge", TW_TYPE_FLOAT, SetMaxAgeCallback, GetMaxAgeCallback, lifeLayer, "group=Other label='Max Particle Age' step=0.1 ");
    TwAddVarCB(bar, "particleSize", TW_TYPE_FLOAT, SetRadiusCallback, GetRadiusCallback, drawer.get(), "group=Other label='Particle Size' min=0.020 step=0.1 ");
//    TwAddVarCB(bar, "maxParticles", TW_TYPE_INT32, SetMaxPCallback, GetMaxPCallback, drawer.get()->particles, "group=Other label='Max Particles' min=0 ");
    TwAddVarCB(bar, "slipParameter", TW_TYPE_FLOAT, SetSlipCallback, GetSlipCallback, drawer.get(), "group=Other label='Slip Parameter' step='0.05' ");
    TwAddVarCB(bar, "potentialDelta", TW_TYPE_FLOAT, SetPotentialDeltaCallback, GetPotentialDeltaCallback, drawer.get(), "group=Other label='Potential Delta' min=0.01 step='0.01' ");

    // Defining groups
    TwSetParam(bar, "Flow", "readonly", TW_PARAM_CSTRING, 1, "false");
    TwSetParam(bar, "Flow", "opened", TW_PARAM_INT32, 1, &(barStates[0]));
    TwSetParam(bar, "Flow", "group", TW_PARAM_CSTRING, 1, "riverManager");

    TwSetParam(bar, "Display", "readonly", TW_PARAM_CSTRING, 1, "false");
    TwSetParam(bar, "Display", "opened", TW_PARAM_INT32, 1, &(barStates[1]));
    TwSetParam(bar, "Display", "group", TW_PARAM_CSTRING, 1, "riverManager");

    TwSetParam(bar, "Other", "readonly", TW_PARAM_CSTRING, 1, "false");
    TwSetParam(bar, "Other", "opened", TW_PARAM_INT32, 1, &(barStates[2]));
    TwSetParam(bar, "Other", "group", TW_PARAM_CSTRING, 1, "riverManager");

    TwSetParam(bar, "riverManager", "readonly", TW_PARAM_CSTRING, 1, "false");
    TwSetParam(bar, "riverManager", "opened", TW_PARAM_INT32, 1, &(barStates[3]));
    TwSetParam(bar, "riverManager", "label", TW_PARAM_CSTRING, 1, getName());

    currentBar = bar;
}

class TweakRiversResource : public ResourceTemplate<55, TweakRivers>
{
public:
    TweakRiversResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<55, TweakRivers> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        checkParameters(desc, e, "name,drawer,active,");

        ptr<DrawRiversTask> drawer = manager->loadResource(getParameter(desc, e, "drawer")).cast<DrawRiversTask>();
        assert(drawer != NULL);
        assert(drawer.cast<DrawRiversTask>() != NULL);

        bool active = true;
        if (e->Attribute("active") != NULL) {
            active = strcmp(e->Attribute("active"), "true") == 0;
        }
        init(drawer, active);
    }
};

extern const char tweakRivers[] = "tweakRivers";

static ResourceFactory::Type<tweakRivers, TweakRiversResource> TweakRiversType;

}
