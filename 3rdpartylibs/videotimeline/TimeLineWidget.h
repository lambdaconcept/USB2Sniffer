#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QScrollArea>
#include "ruler.h"
#include "zoomer.h" 

namespace timeline {

	class TimeLineWidget : public QScrollArea {
		Q_OBJECT
	public:
		TimeLineWidget(QWidget* parent = Q_NULLPTR);
		~TimeLineWidget() = default;

        void appendTimeStampPid(double timestamp, int pid) {
            mRuler->appendTimeStampPid(timestamp, pid);
        }

	private:
		Ruler* mRuler;
		Zoomer* mZoomer;
	};
}

#endif // _MAIN_WINDOW_H
