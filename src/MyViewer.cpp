#include "MyViewer.h"

void MyViewer::add_actions_to_toolBar(QToolBar *toolBar) {
  // Specify the actions :
  DetailedAction *open_mesh =
      new DetailedAction(QIcon(":icons/open.png"), "Open mesh", "Open Mesh",
                         this, this, SLOT(open_mesh()));
  DetailedAction *save_mesh =
      new DetailedAction(QIcon(":icons/save.png"), "Save model", "Save model",
                         this, this, SLOT(save_mesh()));
  DetailedAction *help = new DetailedAction(QIcon(":icons/help.png"), "HELP",
                                            "HELP", this, this, SLOT(help()));
  DetailedAction *saveCamera =
      new DetailedAction(QIcon(":icons/camera.png"), "Save camera",
                         "Save camera", this, this, SLOT(saveCamera()));
  DetailedAction *openCamera =
      new DetailedAction(QIcon(":icons/open_camera.png"), "Open camera",
                         "Open camera", this, this, SLOT(openCamera()));
  DetailedAction *saveSnapShotPlusPlus = new DetailedAction(
      QIcon(":icons/save_snapshot.png"), "Save snapshot", "Save snapshot", this,
      this, SLOT(saveSnapShotPlusPlus()));
  DetailedAction *generateRandom = new DetailedAction(
      QIcon(":icons/generateRandom.png"), "/!\\ EXPERIMENTAL Generate a random skeleton",
      "/!\\ EXPERIMENTAL Generate a random skeleton", this, this, SLOT(generateRandom()));
  DetailedAction *startFromScratch = new DetailedAction(
      QIcon(":icons/startFromScratch.png"), "Start a new skeleton",
      "Start a new skeleton", this, this, SLOT(startFromScratch()));
  DetailedAction *pipeline =
      new DetailedAction(QIcon(":icons/pipeline.png"), "Transform", "Transform",
                         this, this, SLOT(pipeline()));
  DetailedCheckableAction *hideShowSpheres = new DetailedCheckableAction(
      QIcon(":icons/hideShowSpheres.png"), "Hide/Show spheres",
      "Hide/Show spheres", this, this, SLOT(hideShowSpheres()));
  DetailedCheckableAction *hideShowMesh =
      new DetailedCheckableAction(QIcon(":icons/hideShowMesh.png"), "Hide/Show mesh",
                         "Hide/Show mesh", this, this, SLOT(hideShowMesh()));
  DetailedCheckableAction *hideShowHull =
      new DetailedCheckableAction(QIcon(":icons/hideShowHull.png"), "Hide/Show hull",
                         "Hide/Show hull", this, this, SLOT(hideShowHull()));

  // Add them :
  toolBar->addAction(open_mesh);
  toolBar->addAction(save_mesh);
  toolBar->addAction(help);
  toolBar->addSeparator();
  toolBar->addAction(saveCamera);
  toolBar->addAction(openCamera);
  toolBar->addAction(saveSnapShotPlusPlus);
  toolBar->addSeparator();
  toolBar->addAction(startFromScratch);
  toolBar->addAction(generateRandom);
  toolBar->addAction(pipeline);
  toolBar->addSeparator();
  toolBar->addAction(hideShowSpheres);
  toolBar->addAction(hideShowMesh);
  toolBar->addAction(hideShowHull);
}

void MyViewer::draw() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glColor3f(0.2, 0.4, 0.8);
  if (fillMode)
    glPolygonMode(GL_FRONT, GL_FILL);
  else
    glPolygonMode(GL_FRONT, GL_LINE);
  if (displaySpheres) {
    skeleton.draw(selectedName());
    skeleton.drawInterpolation();
  }
  if (displayNormals) {
    skeleton.hullMesh.drawNormals();
  }
  if (displayHull) {
    skeleton.hullMesh.draw();
  }
  // mesh.draw();
}

void MyViewer::postSelection(const QPoint &point) {
  if (selectedName() == -1) {
    cout << "NO SELECTION" << endl;
    selectedNode = nullptr;
    emit(nodeSelected(nullptr));
  } else {
    cout << "SELECTED ELEMENT : " << selectedName()
         << ", selected under pixel (" << point.x() << "," << point.y() << ")"
         << endl;
    selectedNode = skeleton.find(selectedName());
    emit(nodeSelected(selectedNode));
  }
}

void MyViewer::pickBackgroundColor() {
  QColor _bc = QColorDialog::getColor(this->backgroundColor(), this);
  if (_bc.isValid()) {
    this->setBackgroundColor(_bc);
    this->update();
  }
}

void MyViewer::adjustCamera(const point3d &bb, const point3d &BB) {
  point3d const &center = (bb + BB) / 2.f;
  setSceneCenter(qglviewer::Vec(center[0], center[1], center[2]));
  setSceneRadius(1.5f * (BB - bb).norm());
  showEntireScene();
}

void MyViewer::init() {
  makeCurrent();
  initializeOpenGLFunctions();

  setMouseTracking(true); // Needed for MouseGrabber.

  setBackgroundColor(QColor(255, 255, 255));

  // Lights:
  GLTools::initLights();
  GLTools::setSunsetLight();
  GLTools::setDefaultMaterial();

  //
  glShadeModel(GL_SMOOTH);
  glFrontFace(GL_CCW); // CCW ou CW

  glEnable(GL_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glEnable(GL_CLIP_PLANE0);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_COLOR_MATERIAL);

  //
  setSceneCenter(qglviewer::Vec(0, 0, 0));
  setSceneRadius(10.f);
  showEntireScene();
}

QString MyViewer::helpString() const {
  QString text("<h2>Our BMesh Implementation</h2>");
  text += "<p>";
  text += "This is a research application. It is based on an article by "
          "Zhongping Ji, Ligang Liu and ";
  text += "Yigang Wang called \"B-Mesh: A Fast Modeling System for Base "
          "Meshes of 3D Articulated Shapes\".";
  text += "<h3>Participants</h3>";
  text += "<ul>";
  text += "<li>Timothee Chauvin</li>";
  text += "<li>Ginger Delmas</li>";
  text += "<li>Corentin Dumery</li>";
  text += "</ul>";
  text += "<h3>Basics</h3>";
  text += "<p>";

  text += "App actions: <ul>";
  text += "<li>H   :   make this help appear</li>";
  text += "<li>Ctrl + mouse right button double click   :   choose "
          "background color</li>";
  text += "<li>Ctrl + T   :   change window title</li>";

  text += "</ul>Nodes manipulation and visualisation : <ul>";
  text += "<li>R   :   generate a random skeleton";
  text += "<li>S   :   generate a star</li>";
  text += "<li>Backspace   :   suppress the current skeleton to get an initial "
          "and unique "
          "node</li>";
  text += "<li>Shift + mouse left button click   :   select a node</li>";
  text += "<li>A   :   add a node child to the selected node, at the cursor "
          "position</li>";
  text += "<li>M   :   move the selected node to the cursor position</li>";
  text += "<li>V   :   hide/show spheres</li>";
  text += "<li>B   :   hide/show mesh</li>";
  text += "<li>N   :   hide/show hull</li>";

  text += "</ul>Mesh generation : <ul>";
  text += "<li>I   :   interpolate</li>";
  text += "<li>K   :   stitch</li>";
  text += "<li>C   :   subdivise with cattmull</li>";
  text += "<li>E   :   evolve</li>";
  text += "<li>F   :   launch the full pipeline</li>";

  text += "</ul>Other : <ul>";
  text += "<li>L   :   show curvatures</li>";
  text += "</ul>";
  return text;
}

void MyViewer::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_R) {
    skeleton.generateAnimal();
    update();
  } else if (event->key() == Qt::Key_S) {
    skeleton.generateStar();
    update();
  } else if (event->key() == Qt::Key_Backspace) {
    startFromScratch();
  } else if (event->key() == Qt::Key_A) {
    if (selectedNode != nullptr) { // a node is selected
      // the added sphere is denoted by both the position of the cursor and the
      // depth of the mother node

      point3d center = selectedNode->getValue()
                           ->getCenter(); // used to set the missing coordinate
                                          // of the added sphere

      camera()->computeModelViewMatrix(); // necessary to compute the
                                          // (un)projected coordinates

      qglviewer::Vec projCenter = camera()->projectedCoordinatesOf(
          qglviewer::Vec(center[0], center[1],
                         center[2])); // get the coordinates of the mother node
                                      // in the screen system

      point3d pos = camera()->unprojectedCoordinatesOf(
          qglviewer::Vec(cursorT[0], cursorT[1],
                         projCenter[2])); // set the coordinate of the created
                                          // node in the world system

      selectedNode->addChild(new Sphere(pos, 1)); // add the node
      pipeline();
    }
  } else if (event->key() == Qt::Key_M) {
    if (selectedNode != nullptr) {
      point3d center = selectedNode->getValue()
                           ->getCenter(); // used to set the missing coordinate
                                          // for the displacement

      camera()->computeModelViewMatrix(); // necessary to compute the
                                          // (un)projected coordinates

      qglviewer::Vec projCenter = camera()->projectedCoordinatesOf(
          qglviewer::Vec(center[0], center[1],
                         center[2])); // get the coordinates of the node
                                      // in the screen system

      point3d pos = camera()->unprojectedCoordinatesOf(qglviewer::Vec(
          cursorT[0], cursorT[1],
          projCenter[2])); // set the coordinate of the new position of the
                           // node in the world system

      selectedNode->editSphere(
          pos, selectedNode->getValue()->radius); // update position
      emit(nodeSelected(selectedNode));
      pipeline();
    }
  } else if (event->key() == Qt::Key_V) {
    hideShowSpheres();
  } else if (event->key() == Qt::Key_B) {
    hideShowMesh();
  } else if (event->key() == Qt::Key_N) {
    hideShowHull();
  } else if (event->key() == Qt::Key_I) {
    displayHull = false;
    skeleton.interpolate();
    update();
  } else if (event->key() == Qt::Key_K) {
    displayHull = true;
    skeleton.stitching();
    update();
  } else if (event->key() == Qt::Key_E) {
    displayHull = true;
    skeleton.evolve(Itarget, T, 2, 1);
    update();
  } else if (event->key() == Qt::Key_G) {
    displayHull = true;
    skeleton.hullMesh.fairing();
    update();
  } else if (event->key() == Qt::Key_C) {
    displayHull = true;
    skeleton.subdivideHull();
    update();
  } else if (event->key() == Qt::Key_F) {
    pipeline();
  } else if (event->key() == Qt::Key_L) {
    displayHull = true;
    skeleton.hullMesh.computeCurvaturesNorm();
    skeleton.hullMesh.showCurvature = true;
    update();
  } else if (event->key() == Qt::Key_H) {
    help();
  } else if (event->key() == Qt::Key_T) {
    if (event->modifiers() & Qt::CTRL) {
      bool ok;
      QString text =
          QInputDialog::getText(this, tr(""), tr("title:"), QLineEdit::Normal,
                                this->windowTitle(), &ok);
      if (ok && !text.isEmpty()) {
        updateTitle(text);
      }
    }
  }
}

void MyViewer::mouseDoubleClickEvent(QMouseEvent *e) {
  if ((e->modifiers() & Qt::ControlModifier) &&
      (e->button() == Qt::RightButton)) {
    pickBackgroundColor();
    return;
  }

  if ((e->modifiers() & Qt::ControlModifier) &&
      (e->button() == Qt::LeftButton)) {
    showControls();
    return;
  }

  QGLViewer::mouseDoubleClickEvent(e);
}

void MyViewer::mouseMoveEvent(QMouseEvent *e) {

  cursorT[0] = e->pos().x();
  cursorT[1] = e->pos().y();

  QGLViewer::mouseMoveEvent(e);
}

void MyViewer::addSphereToSkeleton(Sphere *sphere) {
  skeleton.getRoot()->addChild(sphere);
  update();
}

void MyViewer::open_mesh() {
  bool success = false;
  QString fileName = QFileDialog::getOpenFileName(nullptr, "", "");
  if (!fileName.isNull()) { // got a file name
    mesh.clear();
    if (fileName.endsWith(QString(".off")))
      success = OFFIO::openTriMesh(fileName.toStdString(), mesh.vertices,
                                   mesh.triangles);
    else if (fileName.endsWith(QString(".obj")))
      success = OBJIO::openTriMesh(fileName.toStdString(), mesh.vertices,
                                   mesh.triangles);
    if (success) {
      std::cout << fileName.toStdString() << " was opened successfully"
                << std::endl;
      point3d bb(FLT_MAX, FLT_MAX, FLT_MAX), BB(-FLT_MAX, -FLT_MAX, -FLT_MAX);
      for (unsigned int v = 0; v < mesh.vertices.size(); ++v) {
        bb = point3d::min(bb, mesh.vertices[v]);
        BB = point3d::max(BB, mesh.vertices[v]);
      }
      adjustCamera(bb, BB);
      update();
    } else
      std::cout << fileName.toStdString() << " could not be opened"
                << std::endl;
  }
}

void MyViewer::save_mesh() {
  bool success = false;
  QString fileName = QFileDialog::getOpenFileName(nullptr, "", "");
  if (!fileName.isNull()) { // got a file name
    if (fileName.endsWith(QString(".off")))
      success =
          OFFIO::save(fileName.toStdString(), mesh.vertices, mesh.triangles);
    else if (fileName.endsWith(QString(".obj")))
      success =
          OBJIO::save(fileName.toStdString(), mesh.vertices, mesh.triangles);
    if (success)
      std::cout << fileName.toStdString() << " was saved" << std::endl;
    else
      std::cout << fileName.toStdString() << " could not be saved" << std::endl;
  }
}

void MyViewer::showControls() {
  // Show controls :
  controls->close();
  controls->show();
}

void MyViewer::saveCameraInFile(const QString &filename) {
  std::ofstream out(filename.toUtf8());
  if (!out)
    exit(EXIT_FAILURE);
  // << operator for point3 causes linking problem on windows
  out << camera()->position()[0] << " \t" << camera()->position()[1] << " \t"
      << camera()->position()[2]
      << " \t"
         " "
      << camera()->viewDirection()[0] << " \t" << camera()->viewDirection()[1]
      << " \t" << camera()->viewDirection()[2] << " \t"
      << " " << camera()->upVector()[0] << " \t" << camera()->upVector()[1]
      << " \t" << camera()->upVector()[2] << " \t"
      << " " << camera()->fieldOfView();
  out << std::endl;

  out.close();
}

void MyViewer::openCameraFromFile(const QString &filename) {

  std::ifstream file;
  file.open(filename.toStdString().c_str());

  qglviewer::Vec pos;
  qglviewer::Vec view;
  qglviewer::Vec up;
  float fov;

  file >> (pos[0]) >> (pos[1]) >> (pos[2]) >> (view[0]) >> (view[1]) >>
      (view[2]) >> (up[0]) >> (up[1]) >> (up[2]) >> fov;

  camera()->setPosition(pos);
  camera()->setViewDirection(view);
  camera()->setUpVector(up);
  camera()->setFieldOfView(fov);

  camera()->computeModelViewMatrix();
  camera()->computeProjectionMatrix();

  update();
}

void MyViewer::openCamera() {
  QString fileName = QFileDialog::getOpenFileName(nullptr, "", "*.cam");
  if (!fileName.isNull()) { // got a file name
    openCameraFromFile(fileName);
  }
}

void MyViewer::saveCamera() {
  QString fileName = QFileDialog::getSaveFileName(nullptr, "", "*.cam");
  if (!fileName.isNull()) { // got a file name
    saveCameraInFile(fileName);
  }
}

void MyViewer::saveSnapShotPlusPlus() {
  QString fileName = QFileDialog::getSaveFileName(nullptr, "*.png", "");
  if (!fileName.isNull()) { // got a file name
    setSnapshotFormat("PNG");
    setSnapshotQuality(100);
    saveSnapshot(fileName);
    saveCameraInFile(fileName + QString(".cam"));
  }
}

void MyViewer::pipeline() {
  int nbFairing = 3;
  displayHull = true;
  displaySpheres = false;
  skeleton.interpolate();
  skeleton.stitching();
  skeleton.subdivideHull();
  skeleton.evolve(Itarget, T, 2, 1);
  skeleton.evolve(Itarget, T, 2, 1);
  skeleton.evolve(Itarget, T, 2, 1);
  skeleton.subdivideHull();
  for (int i = 0; i < nbFairing; i++) {
    skeleton.hullMesh.fairing();
  }
  update();
}

void MyViewer::hideShowSpheres() {
  displaySpheres = !displaySpheres;
  displayHull = false;
  update();
}

void MyViewer::hideShowMesh() {
  fillMode = !fillMode;
  update();
}

void MyViewer::hideShowHull() {
  displayHull = !displayHull;
  update();
}

void MyViewer::generateRandom() {
  skeleton.generateAnimal();
  update();
}

void MyViewer::startFromScratch() {
  selectedNode = nullptr;
  skeleton.clear();
  skeleton.init();
  displaySpheres = true;
  fillMode = true;
  displayHull = false;
  update();
}
