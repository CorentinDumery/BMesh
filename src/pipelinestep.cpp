#include "pipelinestep.h"
#include "ui_pipelinestep.h"

PipelineStep::PipelineStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PipelineStep)
{
    ui->setupUi(this);
}

PipelineStep::~PipelineStep()
{
    delete ui;
}

void PipelineStep::on_buttonInterpolate_clicked() {
    emit(interpolate());
}

void PipelineStep::on_buttonStitch_clicked() {
    emit(stitch());
}

void PipelineStep::on_buttonCatmull_clicked() {
    emit(catmull());
}

void PipelineStep::on_buttonEvolve_clicked() {
    emit(evolve());
}

void PipelineStep::on_buttonFairing_clicked() {
    emit(fairing());
}

