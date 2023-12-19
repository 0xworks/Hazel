# Hazel
Private repository based on (but completely independent to) the Hazel engine described in youtube playlist https://thecherno.com/engine

A quick note on the build system:
At the time I was coding this, I was using vcpkg and had it globally "integrated" with Visual Studio, with a bunch of often used packages already installed.
That means that cmake is able to find the various packages (such as glad, glfw, glm, imgui, and spdlog) that are required to build.

I no longer do things this way (preferring instead to bring in dependencis as git submodules).  However, I have not yet updated this repo to do that, so it will not work out-of-the-box unless you Do Something to allow cmake to find the dependencies.
