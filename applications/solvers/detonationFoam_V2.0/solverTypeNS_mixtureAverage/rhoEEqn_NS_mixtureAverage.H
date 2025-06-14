solve
(
    fvm::ddt(rhoE)
  + fvc::div(rhoEPhi)
);

e = rhoE/rho - 0.5*magSqr(U);
e.correctBoundaryConditions();
thermo.correct();
rhoE.boundaryFieldRef() == rho.boundaryField()*(e.boundaryField()+0.5*magSqr(U.boundaryField()));

/*
solve
(
fvm::ddt(rho, e) - fvc::ddt(rho, e)
- fvm::laplacian(mixAlpha+turbulence->mut()/Prt, e)
+ diffsh
- fvc::div(vk)
);
*/


fvScalarMatrix EEqn
(
	fvm::ddt(rho, e) - fvc::ddt(rho, e)
	- fvm::laplacian(mixAlpha+turbulence->mut()/Prt, e)
	+ diffsh
	- fvc::div(vk)
  ==
    reaction->Qdot()
);
EEqn.relax();

EEqn.solve("e");


thermo.correct();
rhoE = rho*(e + 0.5*magSqr(U));

p.ref() = rho()/psi();
p.correctBoundaryConditions();
rho.boundaryFieldRef() == psi.boundaryField()*p.boundaryField();

Info<< "min/max(p) = "<< min(p).value() << ", " << max(p).value() << endl;
Info<< "min/max(T) = "<< min(T).value() << ", " << max(T).value() << endl;
