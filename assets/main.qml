// 20131024 Simon HSU Image Resize Sample
// use QImage resize function in C++


import bb.cascades 1.0

Page {
    Container {
        //Todo: fill me with QML
        Label {
            // Localized text with the dynamic translation and locale updates support
            text: qsTr("Image Resize") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: SystemDefaults.TextStyles.BigText
        }

        ImageView {
            id: ori
            preferredHeight: 350
            imageSource: "asset:///wallpaper-2349791.jpg"
            scalingMethod: ScalingMethod.AspectFit
        }

        Button {
            text: "resize"
            onClicked: {
                
                // change the image width you want here
                
                _resize.imageResize(ori.imageSource, "/accounts/1000/shared/voice/image.jpg",300);
                resized.imageSource = "file:///accounts/1000/shared/voice/image.jpg"
            }
        }
        
        ImageView {
            id: resized
            scalingMethod: ScalingMethod.AspectFit
        }
    }
}
