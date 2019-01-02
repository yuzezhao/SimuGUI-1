
#include "FMISimulator.h"

#include "FMISupport.h"

FMISimulator::FMISimulator(QWidget *parent) : IMode(parent) {

	setObjectName(QLatin1String("FMISimulator"));
	setDisplayName(tr("FMI\nSimulator"));
	setIcon(QIcon("./Icon/mode/fmi"));

	createWindow();
}

void FMISimulator::createWindow() {

	QWidget *widget = new QWidget();

	QLabel *title = new QLabel();
	title->setText("FMI Simulator");
	QFont font("Microsoft YaHei", 20, 75);
	title->setFont(font);

	QPushButton *b = new QPushButton();
	connect(b, SIGNAL(clicked()), this, SLOT(test()));

	t = new QTextBrowser();

	QGridLayout *layout = new QGridLayout();
	layout->setMargin(10);
	layout->setSpacing(10);
	layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(b, 1, 0, 1, 1);
	layout->addWidget(t, 1, 1, 1, 1);

	widget->setLayout(layout);
	setWidget(widget);
}

void FMISimulator::test() {
	FMISupport *f = new FMISupport();
	t->append(f->loadFMU("D:\\bouncingBall.fmu", FMI_COSIMULATION)->getMessage().c_str());
	t->append(f->simulateByCs(0.0, 30.0, 0.1, false, ',', 0, NULL)->getMessage().c_str());
	//f->unLoad();
}

/*
#include <stdio.h>
#include <iostream>

#include "fmi2.h"
#include "sim_support.h"

using namespace std;

FMU fmu;

int main() {
	//输入参数
	const char* fmuFileName = "bouncingBall.fmu";
	double tEnd = 30.0;//结束时间
	double h = 0.1;//步长
	int loggingOn = 0;
	char csv_separator = ',';
	char **categories = NULL;
	int nCategories = 0;

	//加载fmu
	if (!loadFMU(fmuFileName)) {
		cout << "error!!!" << endl;
		return 0;
	}

	//printf("FMU Simulator: run '%s' from t=0..%g with step size h=%g, loggingOn=%d, csv separator='%c' \n",
	//	fmuFileName, tEnd, h, loggingOn, csv_separator);

	cout << "log categories={ ";
	for (int i = 0; i < nCategories; i++)
		cout << categories[i] << " ";
	cout << "}" << endl;

	simulateByCs(&fmu, tEnd, h, loggingOn, csv_separator, nCategories, categories);
	//simulateByMe(&fmu, tEnd, h, loggingOn, csv_separator, nCategories, categories);

	FreeLibrary(fmu.dllHandle);
	freeModelDescription(fmu.modelDescription);
	if (categories)
		free(categories);
	deleteUnzippedFiles();

	return 1;
}
*/