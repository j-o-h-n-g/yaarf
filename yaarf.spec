Summary: yaarf - Yet Another Alert Reporting Framework
Name: yaarf
Version: 1.1.2
Release: 1%{?dist}
Group: Applications/System
License: LGPLv2
Source: yaarf-%{version}.tar.gz
BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
URL: URL: https://github.com/j-o-h-n-g/yaarf
Provides: libyaarf = %{version}
Requires: glib2 >= 2.22
BuildRequires: pkgconfig >= 0.8
BuildRequires: glib2-devel > 2.10

%description
yaarf is a distributed alert reporting system. It aims to be API compatible with snarf.

%package devel
Summary: Static libraries and C header files for libyaarf
Group: Development/Libraries
Provides: libyaarf-devel = %{version}
Requires: %{name} = %{version}
Requires: pkgconfig >= 1:0.8

%description devel
Static libraries and C header files for libyaarf.


%prep
%setup -q -n %{name}-%{version}

%build
%configure
%{__make}

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{_bindir}
make DESTDIR=%{?buildroot:%{buildroot}} install
%{__rm} -f $RPM_BUILD_ROOT%{_libdir}/*.la

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files -n %{name}
%defattr(-, root, root)
%doc AUTHORS COPYING NEWS 
%{_libdir}/libyaarf*.so*

%files -n %{name}-devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/libyaarf*.a
%{_libdir}/pkgconfig/*
%{_bindir}/yaarftest
