#pragma once

#include <cstddef>

#include <gigperformer/sdk/GPMidiMessages.h>
#include <gigperformer/sdk/GPUtils.h>
#include <gigperformer/sdk/GigPerformerAPI.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "LogWindow.h"

// define an XML string describing your product
const std::string XMLProductDescription =
    // Replace with your information
    "<Library>"
    "<Product Name=\"Hello GP - JUCE\" Version=\"1.0\" BuildDate=\"12/1/2019\"></Product> "
    "<Description>Briefly describe your product</Description>"
    "<ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>"
    "</Library>";

// Define your class here - it MUST be called LibMain and it must inherit from
// GigPerformerAPI

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
  protected:
    // These are for creating menu items in Gig Performer that can be used to trigger external functions provided by the
    // extension developer
    int GetMenuCount() override;
    std::string GetMenuName(int index) override;
    void InvokeMenu(int itemIndex) override;

  public:
    // These must be here but no need to do anything unless you want extra
    // behavior
    LibMain(LibraryHandle handle) : GigPerformerAPI(handle)
    {
    }
    virtual ~LibMain()
    {
    }

    // Now, simply override the callback methods in which you are interested
    // and, in the Initialization method at the end of this class,
    // call RegisterCallback for each of these methods

    void OnOpen() override
    {
        LogWindow::initialize();
    }

    void OnClose() override
    {
        LogWindow::finalize();
    }

    void OnGlobalPlayStateChanged(bool playing) override
    {
        juce::String log = "Playhead ";
        log << (playing ? "playing" : "stopped");

        LogWindow::showWindow();
        LogWindow::log(log);
    }

    // A midi device was added or removed
    void OnMidiDeviceListChanged(std::vector<std::string> &inputs, std::vector<std::string> &outputs) override
    {
        LogWindow::showWindow();

        LogWindow::log("MIDI Inputs/Outputs changed");
        LogWindow::log("===========================");
        LogWindow::log("INPUTS:");
        for (std::size_t i = 0; i < inputs.size(); i++)
            LogWindow::log("\t" + inputs[i]);

        LogWindow::log("\nOUTPUTS:");
        for (std::size_t i = 0; i < outputs.size(); i++)
            LogWindow::log("\t" + outputs[i]);
    }

    void Initialization() override
    {
        // Do any initialization that you need

        // .... your code here

        // Finally, register all the methods that you are going to actually use,
        // i.e, the ones you declared above as override
        registerCallback("OnOpen");
        registerCallback("OnClose");
        registerCallback("OnGlobalPlayStateChanged");
        registerCallback("OnMidiDeviceListChanged");
    }

    // Generally don't touch this - simply define the constant
    // 'XMLProductDescription' at the top of this file with an XML description of
    // your product
    std::string GetProductDescription() override // This MUST be defined in your class
    {
        return XMLProductDescription;
    }
};
