from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import apply_conandata_patches, get

class GameConan(ConanFile):
    name = "Game"
    settings = "os", "compiler", "build_type", "arch"
    license = "MIT"
    description = "Game dev practice project"
    
    def layout(self):
        self.folders.root = ".."
        self.folders.source = "cmake"

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root = True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def requirements(self):
        self.requires("sdl/3.4.8")

    def build(self):
        #apply_conandata_patches(self)
        cmake = CMake(self)
        cmake.configure()
        cmake.build(target = "Game")

    