#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    if(!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }
    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_resize", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("ImageResize_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::imageResize(QString imagePath, QString outputPath, int newWidth)
{
	// outputPath example : "/accounts/1000/shared/voice/image.jpg";

	QImage myImage;
	bool loadImage = myImage.load(imagePath.replace("asset:///","app/native/assets/"));
	float originalW = myImage.width();
	float originalH = myImage.height();
	float ratio = originalH / originalW;
	qDebug() << "imagePath : " << imagePath;
	qDebug() << "imagePath2 : " << imagePath.replace("asset:///","app/native/assets/");
	qDebug() << "loadImage : " << loadImage;
	qDebug() << "ori width : " << myImage.width() << "ori height : " << myImage.height();
	qDebug() << "ratio : " << ratio;

	// input whatever width you want as newImageWidth
	int newImageWidth = newWidth;

	int newImageHeight= newImageWidth * ratio;

	// sometimes the scaled may need both width and height all even.. so add the code below
	// may be it can be removed...

	qDebug() << "newImageHeight before : " << newImageHeight;
	if (newImageHeight %2 != 0 )
	{
		newImageHeight = newImageHeight +1;
	}
	qDebug() << "newImageHeight after : " << newImageHeight;

	QImage result = myImage.scaled(newImageWidth, newImageHeight); //.scaled(800, 800*ratio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	qDebug() << "width : " << result.width() << "height : " << result.height();
	QString tempFile = outputPath;
	result.save(tempFile, "JPG");
}
