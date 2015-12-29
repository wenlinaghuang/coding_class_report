#include<iostream>
#include<stdlib.h>
#include"element.h"
#include"element_advance.h"
#include<vector>
#include"TH1D.h"
#include"THStack.h"
#include"TCanvas.h"
#include"TGraph.h"

using namespace std;
void final_project()
{
	double Lead_per_Month,Cost_per_Lead,Conversion_Rate,Profit_per_Sale,Overhead_per_Month = 800.0;
	THStack *hs = new THStack("hs","");
	
	cout << "Input Lead per Month: ";
	cin >>Lead_per_Month;
	cout << "Input Cost per Lead: ";
	cin >> Cost_per_Lead;	
	cout << "Input Conversion Rate: ";
	cin >> Conversion_Rate;
	cout << "Input Profit per Sale: ";
	cin >> Profit_per_Sale;
	Element E(Lead_per_Month,Cost_per_Lead,Conversion_Rate,Profit_per_Sale,Overhead_per_Month);
    
	Element_advance EA(Lead_per_Month,Cost_per_Lead,Conversion_Rate,Profit_per_Sale,Overhead_per_Month);
	
	E.Leads_per_Month_Rand();
//	E.Show_L();
	E.Cost_per_Lead_Rand();
//	E.Show_C();
	E.Conversion_Rate_Rand();
//	E.Show_R();
	E.Profit_per_Sale_Rand();
//	E.Show_P();

	E.profit_caculation();
	//E.Show_Prof();

	E.no_distribution_sort();

    E.Uniform_distribution_sort();
	E.Gaus_distribution_sort();
	E.Landau_distribution_sort();
    E.Exp_distribution_sort();
	EA.Buying_People_Decay_Graph();
	cout << "flag1" <<endl;
	E.Buying_People_Decay_each_region();
	E.BPD_sorting();
	E.Show_ProfD0();
	E.Show_ProfD1();
	int n_bin = (*(E.itsma)-E.vitsmi)/10.0;
	int g_bin = (*(E.itsnma)-E.vitsnmi)/10.0;
	int l_bin = (*(E.itslma)-E.vitslmi)/10.0;
    int u_bin = (*(E.itsuma)-E.vitsumi)/10.0;
    TH1D *f1 = new TH1D("f1","f1",n_bin,(E.vitsmi),*(E.itsma));
    for(std::vector<double>::iterator it = E.vec_Prof.begin();it!=E.vec_Prof.end();it++)
    f1->Fill(*it);
	f1->SetFillColor(kBlue);
    //hs->Add(f1);
	TH1D *f2 = new TH1D("f2","f2",g_bin,(E.vitsnmi),*(E.itsnma));
	for(std::vector<double>::iterator it2 = E.vec_ProfN.begin();it2!=E.vec_ProfN.end();it2++)
  	f2->Fill(*it2);
	f2->SetFillColor(kGreen);
    //hs->Add(f2);
	TH1D *f3 = new TH1D("f3","f3",500,(E.vitslmi),10000);
	for(std::vector<double>::iterator it3 = E.vec_ProfP.begin();it3!=E.vec_ProfP.end();it3++)
	f3->Fill(*it3);
	f3->SetFillColor(6);
    TH1D *f4 = new TH1D("f4","f4",500,(E.vitsemi),*(E.itsema));
    for(std::vector<double>::iterator it4 = E.vec_ProfE.begin();it4!=E.vec_ProfE.end();it4++)
    f4->Fill(*it4);
    f4->SetFillColor(29);
	//hs->Add(f3);
    TH1D *f5 = new TH1D("f5","f5",500,(E.vitsumi),*(E.itsuma));
    for(std::vector<double>::iterator it5 = E.vec_ProfU.begin();it5!=E.vec_ProfU.end();it5++)
    f5->Fill(*it5);
    f5->SetFillColor(29);
	TCanvas *cs = new TCanvas("cs","cs",700,900);
	cs->Divide(3,2);
	//cs->cd(1); hs->Draw();
	cs->cd(1); f1->Draw();
	cs->cd(2); f2->Draw();
	cs->cd(3); f3->Draw();
    cs->cd(4); f4->Draw();
	cs->cd(5); f5->Draw();	
	//cs->cd(6); hs->Draw();
	//*declare for TGraph parameter
	double day[6] = {1.,7.,13.,19.,25.,31.};
	double nbpa[6];
	std::vector<double>::iterator itnbp=EA.nbp.begin();
	/*cout << *(itnbp)<<endl;*/
	for(int i = 0;i<6;i++){
		nbpa[i] = *(itnbp);
		itnbp++;
	}
	//cs2 of the graph
	THStack *hs2 = new THStack("hs2","");
	int bpd0_bin = (*(E.itbpdsma0)-(E.vitsbpdmi0))/10.0;
	int bpd1_bin = (*(E.itbpdsma1)-(E.vitsbpdmi1))/10.0;
    int bpd2_bin = (*(E.itbpdsma2)-(E.vitsbpdmi2))/10.0;
	int bpd3_bin = (*(E.itbpdsma3)-(E.vitsbpdmi3))/10.0;
	int bpd4_bin = (*(E.itbpdsma4)-(E.vitsbpdmi4))/10.0;
	int bpd5_bin = (*(E.itbpdsma5)-(E.vitsbpdmi5))/10.0;	
	
	TGraph *g1 = new TGraph(6,day,nbpa);
	g1->SetMarkerColor(kRed);
	g1->SetMarkerStyle(20);
	
	TCanvas *cs2 = new TCanvas("cs2","cs2",700,900);
	cs2->cd(1);g1->Draw("AP");

	TH1D *fdr0 = new TH1D("fdr0","fdr0",bpd0_bin,E.vitsbpdmi0,*(E.itbpdsma0));
	for(std::vector<double>::iterator itdr0=E.nbpder_Prof0.begin();itdr0!=E.nbpder_Prof0.end();itdr0++)
	fdr0->Fill(*itdr0);
	fdr0->SetFillColor(kBlue);

	TH1D *fdr1 = new TH1D("fdr1","fdr1",bpd1_bin,E.vitsbpdmi1,*(E.itbpdsma1));
    for(std::vector<double>::iterator itdr1=E.nbpder_Prof1.begin();itdr1!=E.nbpder_Prof1.end();itdr1++)
    fdr1->Fill(*itdr1);
    fdr1->SetFillColor(2);
	
	TH1D *fdr2 = new TH1D("fdr2","fdr2",bpd2_bin,E.vitsbpdmi2,*(E.itbpdsma2));
    for(std::vector<double>::iterator itdr2=E.nbpder_Prof2.begin();itdr2!=E.nbpder_Prof2.end();itdr2++)
    fdr2->Fill(*itdr2);
    fdr2->SetFillColor(3);

	TH1D *fdr3 = new TH1D("fdr3","fdr3",bpd3_bin,E.vitsbpdmi3,*(E.itbpdsma3));
    for(std::vector<double>::iterator itdr3=E.nbpder_Prof3.begin();itdr3!=E.nbpder_Prof3.end();itdr3++)
    fdr3->Fill(*itdr3);
    fdr3->SetFillColor(5);
	
	TH1D *fdr4 = new TH1D("fdr4","fdr4",bpd4_bin,E.vitsbpdmi4,*(E.itbpdsma4));
    for(std::vector<double>::iterator itdr4=E.nbpder_Prof4.begin();itdr4!=E.nbpder_Prof4.end();itdr4++)
    fdr4->Fill(*itdr4);
    fdr4->SetFillColor(9);

	TH1D *fdr5 = new TH1D("fdr5","fdr5",bpd5_bin,E.vitsbpdmi5,*(E.itbpdsma5));
    for(std::vector<double>::iterator itdr5=E.nbpder_Prof5.begin();itdr5!=E.nbpder_Prof5.end();itdr5++)
    fdr5->Fill(*itdr5);
    fdr5->SetFillColor(kBlue);

	TCanvas *cs3 = new TCanvas("cs3","cs3",700,900);
	cs3->Divide(3,2);
	cs3->cd(1); fdr0->Draw();
	cs3->cd(2); fdr1->Draw();
	cs3->cd(3); fdr2->Draw();
	cs3->cd(4); fdr3->Draw();
	cs3->cd(5); fdr4->Draw();
	cs3->cd(6); fdr5->Draw();

}

	
