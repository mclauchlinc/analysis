// Call this at the top of your program when you would initialize all the
// histograms
void makeHists_fid() {
  double min_phi[6] = {0, 60, 120, -180, -120, -60};
  double max_phi[6] = {60, 120, 180, -120, -60, 0};
  for (int sec = 0; sec < sector_num; sec++) {
    sprintf(hname, "fid_sec%d", sec + 1);
    sprintf(htitle, "fid_sec%d", sec + 1);
    fid_sec_hist[sec] = new TH2D(hname, htitle, bins, min_phi[sec],
                                 max_phi[sec], bins, theta_min, theta_max);
  }
}

// When you want to fill call this putting the in the appropriate values either
// from the banks or by calculating them
void Fill_fid(double theta, double phi, int sector) {
  fid_sec_hist[sector]->Fill(phi, theta);
}

// Call this at the end of your program to write all the fiducial hists
void Fid_Write() {
  for (int sec = 0; sec < sector_num; sec++) {
    fid_sec_hist[sec]->SetYTitle("#theta");
    fid_sec_hist[sec]->SetXTitle("#phi");
    fid_sec_hist[sec]->Write();
  }
}