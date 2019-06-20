#ifndef PIPELINESTEP_H
#define PIPELINESTEP_H

#include <QWidget>

namespace Ui {
class PipelineStep;
}

class PipelineStep : public QWidget {
  Q_OBJECT

public:
  explicit PipelineStep(QWidget *parent = 0);
  ~PipelineStep();

private:
  Ui::PipelineStep *ui;

private slots:
  void on_buttonInterpolate_clicked();
  void on_buttonStitch_clicked();
  void on_buttonCatmull_clicked();
  void on_buttonEvolve_clicked();
  void on_buttonFairing_clicked();

signals:
  void interpolate();
  void stitch();
  void catmull();
  void evolve();
  void fairing();
};

#endif // PIPELINESTEP_H
