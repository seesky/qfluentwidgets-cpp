#include "smooth_scroll.h"

SmoothScroll::SmoothScroll(QAbstractScrollArea *widget, Qt::Orientation orient)
{
    this->widget = widget;
    this->orient = orient;
    this->fps = 60;
    this->duration = 400;
    this->stepsTotal = 0;
    this->stepRatio = 1.5;
    this->acceleration = 1;
    this->lastWheelEvent = nullptr;
    this->scrollStamps = new QList<int>();
    this->stepsLeftQueue = new QList<float *>();
    this->smoothMoveTimer = new QTimer(widget);
    this->smoothMode = SmoothMode::LINEAR;
    this->smoothMoveTimer->connect(this->smoothMoveTimer, SIGNAL(QTimer::timeout), SLOT(this->__smoothMove));
    //this->smoothMoveTimer->connect(this->smoothMoveTimer, &QTimer::timeout, this->smoothMoveTimer, &SmoothScroll::__smoothMove); //TODO:特别关注
}

void SmoothScroll::setSmoothMode(SmoothMode smoothMode)
{
    this->smoothMode = smoothMode;
}

void SmoothScroll::wheelEvent(QWheelEvent *e)
{
    int delta;
    if(e->angleDelta().y() != 0){
        delta = e->angleDelta().y();
    }else{
        delta = e->angleDelta().x();
    }
    
    if((this->smoothMode == SmoothMode::NO_SMOOTH) || ((abs(delta) % 120) != 0)){
        //TODO:QAbstractScrollArea.wheelEvent(self.widget, e)
        //QAbstractScrollArea *asa = new QAbstractScrollArea(this->widget);
        //asa->wheelEvent(e);
        return;
    }

    int now = QDateTime().currentDateTime().toMSecsSinceEpoch();
    this->scrollStamps->append(now);
    while((now - this->scrollStamps->at(0)) > 500){
        this->scrollStamps->pop_front();
    }

    float accerationRatio = qMin(this->scrollStamps->length() / 15, 1);
    if(!this->lastWheelEvent)
    {
        this->lastWheelEvent = new QWheelEvent(*e);
    }else{
        this->lastWheelEvent = e;
    }

    this->stepsTotal = this->fps * this->duration / 1000;

    delta = delta * this->stepRatio;
    if(this->acceleration > 0)
    {
        delta += delta * this->acceleration * accerationRatio;
    }

    float array[] = {delta, this->stepsTotal};
    this->stepsLeftQueue->append(array);

    this->smoothMoveTimer->start(int(1000 / this->fps));
}

void SmoothScroll::__smoothMove()
{
    float totalDelta = 0;
    QList<float *>::iterator it;
    for (it = this->stepsLeftQueue->begin(); it != this->stepsLeftQueue->end(); ++it) {
        totalDelta += this->__subDelta(*it[0], *it[1]);
        *it[1] -= 1;
    }

    while(!this->stepsLeftQueue->isEmpty() && this->stepsLeftQueue->at(0)[1] == 0)
    {
        this->stepsLeftQueue->pop_front();
    }

    QPoint *p;
    QScrollBar *bar;
    if(this->orient == Qt::Vertical)
    {
        p = new QPoint(0, qRound(totalDelta));
        bar = this->widget->verticalScrollBar();
    }else{
        p = new QPoint(qRound(totalDelta), 0);
        bar = this->widget->horizontalScrollBar();
    }

    QWheelEvent *e = new QWheelEvent(
        this->lastWheelEvent->pos(),
        this->lastWheelEvent->globalPos(),
        QPoint(),
        *p,
        qRound(totalDelta),
        this->orient,
        this->lastWheelEvent->buttons(),
        Qt::NoModifier
    );

    QApplication::sendEvent(bar, e);

    if(this->stepsLeftQueue->isEmpty())
    {
        this->smoothMoveTimer->stop();
    }
}

float SmoothScroll::__subDelta(float delta, float stepsLeft)
{
    float m = this->stepsTotal / 2;
    float x = qAbs(this->stepsTotal - stepsLeft - m);

    float res = 0;
    if(this->smoothMode == SmoothMode::NO_SMOOTH){
        res = 0;
    }else if(this->smoothMode == SmoothMode::CONSTANT){
        res = delta / this->stepsTotal;
    }else if(this->smoothMode == SmoothMode::LINEAR){
        res = 2 * delta / this->stepsTotal * (m - x) / m;
    }else if(this->smoothMode == SmoothMode::QUADRATI){
        res = 3 /4 / m * (1 - x * x / m / m) * delta;
    }else if(this->smoothMode == SmoothMode::COSINE){
        res = (cos(x * M_PI / m) + 1) / (2 * m) * delta;
    }

    return res;
}