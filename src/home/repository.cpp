#include "home/repository.h"

HomeRepository::HomeRepository() {
}

HomeRepository::~HomeRepository() {
}

QList<SFuncItemData> HomeRepository::datas() {
    return {
        SFuncItemData{
            EFunc::FuncConversion,
            EFuncItemBtnType::AddFile,
            "Image Converter",
            "Convert images to other formats.",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncCompression,
            EFuncItemBtnType::AddFile,
            "Background Remover",
            "Automatically remove backgrounds from images.",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/BGRemover.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncCropping,
            EFuncItemBtnType::AddFile,
            "GIF Maker",
            "Create a GIF from multiple images.",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/Gifmaker.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncErase,
            EFuncItemBtnType::AddFile,
            "Watermark Remover",
            "Batch remove watermarks from images.",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/AIRemoveWatermark.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncEnhancement,
            EFuncItemBtnType::AddFile,
            "Image Enhancer",
            "Batch enhance images with AI for improved clarity and quality.",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/AIImageEnhance.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncInpainting,
            EFuncItemBtnType::AddFile,
            "功能1",
            "这是功能1的描述",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncEffects,
            EFuncItemBtnType::AddFile,
            "功能1",
            "这是功能1的描述",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        },
        SFuncItemData{
            EFunc::FuncGifGeneration,
            EFuncItemBtnType::AddFile,
            "功能1",
            "这是功能1的描述",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(),
            QPixmap(":/images/addfile_icon1.png")
        }
    };
}
