%{!?directory:%define directory /usr}

%define buildroot %{_tmppath}/%{name}

Name:          tcl-lzf
Summary:       Tcl interface for liblzf
Version:       0.6
Release:       1
License:       BSD-2-Clause
Group:         Development/Libraries/Tcl
Source:        Tcl-lzf-%version.tar.gz
URL:           https://github.com/ray2501/Tcl-lzf
BuildRequires: autoconf
BuildRequires: make
BuildRequires: tcl-devel >= 8.4
BuildRoot:     %{buildroot}

%description
LZF is an extremely fast (not that much slower than a pure memcpy) compression 
algorithm. It is ideal for applications where you want to save *some* space but 
not at the cost of speed. It is ideal for repetitive data as well. The module is 
self-contained and very small.

Tcl-lzf is Tcl interface for Liblzf.

%prep
%setup -q -n Tcl-lzf-%{version}

%build
./configure \
	--prefix=%{directory} \
	--exec-prefix=%{directory} \
	--libdir=%{directory}/%{_lib}
make 

%install
make DESTDIR=%{buildroot} pkglibdir=%{tcl_archdir}/%{name}%{version} install

%clean
rm -rf %buildroot

%files
%defattr(-,root,root)
%{tcl_archdir}
