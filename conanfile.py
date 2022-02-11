
from conans import ConanFile, CMake

class Conan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "asio/1.19.2",\
               "sfml/2.5.1"

    generators = "cmake", "cmake_find_package", "cmake_paths"
    def configure(self):
        self.options["SFML"].shared = True
        if "shared" in self.options:
            pass

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="")
        cmake.build()