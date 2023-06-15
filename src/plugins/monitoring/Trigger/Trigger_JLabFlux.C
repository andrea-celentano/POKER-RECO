// hnamepath: /Trigger/hTriggerBits
// hnamepath: /Trigger/hTriggerMultiplicity
// hnamepath: /Trigger/hTriggerTimes
// hnamepath: /Trigger/hTriggerTimes2D

{
	TDirectory *dir = (TDirectory*)gDirectory->FindObjectAny("TriggerTimes");
	if(dir) dir->cd();

	TH1D *hTriggerBits=0;
	TH1D *hTriggerTimes=0;
	TH1D *hTriggerMultiplicity=0;
	TH2D *hTriggerTimes2D=0;

	hTriggerBits=(TH1D*)gDirectory->FindObjectAny("hTriggerBits");
	hTriggerMultiplicity=(TH1D*)gDirectory->FindObjectAny("hTriggerMultiplicity");
	hTriggerTimes=(TH1D*)gDirectory->FindObjectAny("hTriggerTimes");
	hTriggerTimes2D=(TH2D*)gDirectory->FindObjectAny("hTriggerTimes2D");


	if(gPad == NULL) {
		TCanvas *c1 = new TCanvas("cTrigger");
		c1->cd(0);
		c1->Draw();
		c1->Update();
	}

	if(!gPad) return;
	TCanvas *c1 = gPad->GetCanvas();
	c1->Divide(2, 2);

	c1->cd(1);
	if (hTriggerMultiplicity) hTriggerMultiplicity->Draw("HIST");
	c1->cd(2);
	if (hTriggerBits) hTriggerBits->Draw("HIST");
	c1->cd(3)->SetLogy();
	if (hTriggerTimes) hTriggerTimes->Draw("HIST");
	c1->cd(4)->SetLogz();
	if (hTriggerTimes2D) hTriggerTimes2D->Draw("colz");
}
