#pragma once

#include "terrainlab/ImageRenderer.h"
#include "terrainlab/OverlayRenderer.h"
#include "terrainlab/FullView2dRenderer.h"
#include "terrainlab/FullView3dRenderer.h"
#include "terrainlab/Clipmap2dRenderer.h"
#include "terrainlab/Clipmap3dRenderer.h"
#include "terrainlab/VTexRenderer.h"
#include "terrainlab/TerrainRenderer.h"

#include <ee0/typedef.h>
#include <ee3/WxStageCanvas.h>
#include <blueprint/typedef.h>
#include <blueprint/WxGraphPage.h>

#include <node0/typedef.h>
#include <terraingraph/typedef.h>
#include <terraingraph/DeviceVarType.h>

#include <array>

namespace terrainlab
{

class WxGraphPage;

class WxPreviewCanvas : public ee3::WxStageCanvas
{
public:
    WxPreviewCanvas(const ur::Device& dev, ee0::WxStagePage* stage, ECS_WORLD_PARAM
        const ee0::RenderContext& rc);
    virtual ~WxPreviewCanvas();

    virtual void OnNotify(uint32_t msg, const ee0::VariantSet& variants) override;

    void SetGraphPage(const bp::WxGraphPage<terraingraph::DeviceVarType>* graph_page);

    void InitEditOP();

protected:
    virtual void DrawBackground3D() const override;
    virtual void DrawForeground3D() const override;
    virtual void DrawForeground2D() const override;

private:
    void OnSelectionInsert(const ee0::VariantSet& variants);

    void DrawSelected(tess::Painter& pt, const sm::mat4& cam_mat,
        const pt0::RenderContext& rc) const;

    void SetupRenderer();

    bp::NodePtr GetSelectedNode() const;
    terraingraph::DevicePtr GetSelectedDevice() const;

private:
    enum OperatorID
    {
        OP_CAMERA_2D,
        OP_CAMERA_3D,

        OP_TEMP_BRUSH,
        OP_NOISE_BRUSH,

        OP_CAM_CLIPMAP,

        OP_MAX_NUM
    };

private:
    const bp::WxGraphPage<terraingraph::DeviceVarType>* m_graph_page = nullptr;

    n0::SceneNodePtr m_selected = nullptr;

    std::shared_ptr<rp::HeightfieldRenderer> m_hf_rd = nullptr;
    ImageRenderer   m_img_rd;
    OverlayRenderer m_overlay_rd;

    FullView2dRenderer m_full2_rd;
    FullView3dRenderer m_full3_rd;
    Clipmap2dRenderer  m_clip2_rd;
    Clipmap3dRenderer  m_clip3_rd;
    VTexRenderer       m_vtex_rd;

    TerrainRenderer m_terr_rd;

    std::array<ee0::EditOPPtr, OP_MAX_NUM> m_ops;

    pt0::CameraPtr m_cam2d = nullptr;
    pt0::CameraPtr m_cam3d = nullptr;

}; // WxPreviewCanvas

}