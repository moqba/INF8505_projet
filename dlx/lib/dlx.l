notebook {} {} {} {
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text Registers} {
        screeno {R 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {R0..7} -labelwidth 3 -scrolled 0 -nbr_fields 8 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        screeno {R 8 -type w32 -radix default -addr_radix default -format string -width 16 -label {R8..15} -labelwidth 3 -scrolled 0 -nbr_fields 8 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        screeno {R 16 -type w32 -radix default -addr_radix default -format string -width 16 -label {R16..23} -labelwidth 3 -scrolled 0 -nbr_fields 8 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        screeno {R 24 -type w32 -radix default -addr_radix default -format string -width 16 -label {R24..31} -labelwidth 3 -scrolled 0 -nbr_fields 8 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        column {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
            screeno {PC 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            screeno {LR 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            screeno {SP 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            screeno {PH 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            screeno {PL 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            screeno {MC 0 -type uint1 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text Memories} {
        screeno {DMw 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
        screeno {DMw 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 10 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text Bypasses} {
        column {-bd 0 -relief flat -width 0 -height 0} {-fill y } {} {
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {} {
                label {-bd 3 -relief ridge -background grey80 -text ID} {-fill both -expand true } {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {} {
                label {-bd 3 -relief ridge -background grey80 -text EX} {-fill both -expand true } {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {}
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {} {
                label {-bd 3 -relief ridge -background grey80 -text ME} {-fill both -expand true } {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {}
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {} {
                label {-bd 3 -relief ridge -background grey80 -text WB} {-fill both -expand true } {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true } {}
        }
        column {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {r1 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
                screeno {r2 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {__pS1_r 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {pS1} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
                screeno {__pS2_r 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {pS2} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {pd1w 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {__pD1_r 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {pD1} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {pe1w 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {__pE1_r 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {pE1} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
            row {-bd 0 -relief flat -width 0 -height 0} {-fill both -expand true} {} {
                screeno {w1 0 -type w32 -radix default -addr_radix default -format string -width 16 -label {} -labelwidth 5 -scrolled 1 -nbr_fields 10 -read_only 0 -hide_addresses 0} {-fill none -expand false} {}
            }
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text Statistics} {
        row {-bd 10 -relief flat} {-fill both -expand true} {} {
            column {-bd $::gui::tctborderwidth -relief raised} {} {} {
                pchist {-show_stage_names 1 -nr_pcs 5 } {} {}
            }
            column {-bd $::gui::tctborderwidth -relief raised} {} {} {
                instrhist {-show_stage_names 0 -nr_instrs 5 -radix hexadecimal } {} {}
            }
            column {-bd $::gui::tctborderwidth -relief raised} {} {} {
                instrcnt {} {} {}
            }
            column {-bd $::gui::tctborderwidth -relief raised} {} {} {
                stack {} {} {}
            }
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "Screen output"} {
        screenof {} {-fill both -expand true} {}
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "File output"} {
        pane {-side top} {} {} {
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                fileof {} {-fill both -expand true} {}
            }
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                fileorf {} {-fill both -expand true} {}
            }
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "File input"} {
        pane {-side top} {} {} {
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                fileif {} {-fill both -expand true} {}
            }
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                fileirf {} {-fill both -expand true} {}
            }
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "Graphical output"} {
        pane {-side top} {} {} {
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                grof {} {-fill both -expand true} {}
            }
            paned_frame {-bd 0 -relief flat} {-fill both -expand true} {-weight 100} {
                grrof {} {-fill both -expand true} {}
            }
        }
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "Variable Info" } {
        varinfo {} {-fill both -expand true} {}
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "Locals " } {
        varinfo {0} {-fill both -expand true} {}
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text "Hosted terminal"} {
        stdio {} {-fill both -expand true} {}
    }
    notebook_tab {-bd 0 -relief flat} {-fill both -expand true} {-text Pipeline} {
        pipeline {-label_type f -hide_copies 1} {-fill both -expand true} {}
    }
}
