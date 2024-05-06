


## QScintilla installation
1. Download repository 'git clone --recursive-submodules https://github.com/mneuroth/QuickScintilla.git'
1. Run QtCreator, open project form file QScintilla->src->qscintilla.pro
1. Rebuild project
1. In QtCreator open "Projects" -> "Build and Run" -> Select "Run" for current build kit -> "Run Settings" -> "Add Deploy Step" -> "make" -> "Make arguments" paste "install" 
1. Then select form menu "Build" -> "Deploy"