//
//  CDFaceData.h
//  candide
//
//  Created by damian on 03/11/13.
//  Copyright (c) 2013 Damian Stewart. All rights reserved.
//

#ifndef __candide__CandideFaceData__
#define __candide__CandideFaceData__

#include <iostream>

#include <string>
#include <map>
#include <vector>
#include "picojson.h"
#include <sigc++/sigc++.h>

#include "CDMesh.h"
#include "CDMeshMapper.h"

class CDFaceDistortionUnit {
public:
    CDFaceDistortionUnit(const std::string& name = "");
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }

    void addVertexOffset(unsigned short vIdx, glm::vec3 offset);

    /// apply this shape unit to the target mesh with the given factor (usually 0..1)
    void apply(float amount, CDMesh& target) const;

    std::map<unsigned short, glm::vec3> offsets;

private:
    std::string name;
};

class CDFaceData {
public:
    /// filename is in wfm format, see candide3
    CDFaceData(const std::string& path);

    void clear();

    void calculateCompensatoryTranslateScale(const glm::vec3& centerPos, const glm::vec3& fitSize, glm::vec3& tranlateOut, float& scaleOut);
    void draw();

    std::vector<std::string> getAnimationUnitNames();
    std::vector<std::string> getShapeUnitNames();

    float getAnimationUnitValue(const std::string& auName) const;
    void setAnimationUnitValue(const std::string& auName, float value);

    float getShapeUnitValue(const std::string& suName) const;
    void setShapeUnitValue(const std::string& suName, float value);

    void deserialize(const picojson::value& source);
    picojson::value serialize() const;

    CDMesh getDistortedMesh() const;

    const CDMesh& getControlMeshForMeanValueDeformation();

    sigc::signal<void> controlMeshChangedSignal;

    std::vector<CDFaceDistortionUnit> shapeUnits;
    std::vector<CDFaceDistortionUnit> animationUnits;

private:
    void load(const std::string& path);

    /// returns npos if not found
    size_t getIndexOfShapeUnit(const std::string& name) const;
    size_t getIndexOfAnimationUnit(const std::string& name) const;

    // data
    CDMesh meshAtRest;

    // settings for distortion
    std::map<size_t, float> shapeUnitSettings;
    std::map<size_t, float> animationUnitSettings;
    ;

    CDMesh controlMeshForMeanValueDeformation;
    CDMeshMapper controlMeshMapper;
};

#endif /* defined(__candide__CandideFaceData__) */
