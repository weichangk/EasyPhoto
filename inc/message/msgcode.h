#pragma once

enum EMsgCode {
    // func change
    MsgCode_FuncChange = 1000,

    // upsc
    MsgCode_Upsc_Start = 2000,
    MsgCode_Upsc_Progress,
    MsgCode_Upsc_Cancel,
    MsgCode_Upsc_Finish,
    MsgCode_Upsc_Error,

    // comp
    MsgCode_Comp_Start = 3000,
    MsgCode_Comp_Progress,
    MsgCode_Comp_Cancel,
    MsgCode_Comp_Finish,
    MsgCode_Comp_Error,

    // conv
    MsgCode_Conv_Start = 4000,
    MsgCode_Conv_Progress,
    MsgCode_Conv_Cancel,
    MsgCode_Conv_Finish,
    MsgCode_Conv_Error,

    // crop
    MsgCode_Crop_Start = 5000,
    MsgCode_Crop_Progress,
    MsgCode_Crop_Cancel,
    MsgCode_Crop_Finish,
    MsgCode_Crop_Error,

    // erase
    MsgCode_Erase_Start = 6000,
    MsgCode_Erase_Progress,
    MsgCode_Erase_Cancel,
    MsgCode_Erase_Finish,
    MsgCode_Erase_Error,

    // gifmk
    MsgCode_GifMk_Start = 7000,
    MsgCode_GifMk_Progress,
    MsgCode_GifMk_Cancel,
    MsgCode_GifMk_Finish,
    MsgCode_GifMk_Error,

    // bgrm
    MsgCode_BgRm_Start = 8000,
    MsgCode_BgRm_Progress,
    MsgCode_BgRm_Cancel,
    MsgCode_BgRm_Finish,
    MsgCode_BgRm_Error,

    // thumbmk
    MsgCode_ThumbMk_Start = 9000,
    MsgCode_ThumbMk_Progress,
    MsgCode_ThumbMk_Cancel,
    MsgCode_ThumbMk_Finish,
    MsgCode_ThumbMk_Error,

    // imgdl
    MsgCode_ImgDl_Start = 10000,
    MsgCode_ImgDl_Progress,
    MsgCode_ImgDl_Cancel,
    MsgCode_ImgDl_Finish,
    MsgCode_ImgDl_Error,
};