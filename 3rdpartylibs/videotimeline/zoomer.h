#ifndef _ZOOMER_H
#define _ZOOMER_H

#include <QWidget> 
#include <QToolButton>
#include <QSlider>

#define MAX_LEVEL 8
#define MIN_LEVEL 1

namespace timeline {

	class Zoomer : public QWidget {

		Q_OBJECT
	public:
		Zoomer(QWidget* parent = Q_NULLPTR);
		void initializeControls();
		~Zoomer() = default;

	signals:
		void zoomerIn(int level);
		void zoomerOut(int level);

	public slots:
		void onZoomInClicked(bool checked);
		void onZoomOutClicked(bool checked); 
		void onSliderChanged(int value);
		void onChangeSliderPosition(int level);

	private: 
		QToolButton* mZoomIn;
		QToolButton* mZoomOut;
		QSlider* mZoomSlider;
		int mCurrentLevel;
	};
	 
}


#endif