#include "readChemistryProperties.H"
#include "createDiffFields.H"
#include "createTDiffFields.H"
#include "createLambdaFields.H"
#include "createMuFields.H"

#include "readTranData.H"
#include "readBinaryDiff.H"
#include "readThermalDiff.H"
#include "readSpeciesLambda.H"
#include "readSpeciesMu.H"

while (runTime.run())
{
#include "updateTransProperties.H"
#include "detoCellular.H"

runTime++;
mesh.update();

#include "calculateDt.H"

Info<< "Time = " << runTime.timeName() << nl << endl;
//fluxSchemeFields->update(rho,U,e,p,c,phi,rhoPhi,rhoUPhi,rhoEPhi);
fluxSchemeFields->update(rho,rhoU,e,rPsi,c,phi,rhoPhi,rhoUPhi,rhoEPhi);

#include "rhoEqn_NS_mixtureAverage.H"
#include "rhoUEqn_NS_mixtureAverage.H"
#include "rhoYEqn_NS_mixtureAverage.H"
#include "rhoEEqn_NS_mixtureAverage.H"

turbulence->correct();
thermophysicalTransport->correct();

runTime.write();

Info<< "ExecutionTime = "<< runTime.elapsedCpuTime() << " s" << nl << endl;
Info<< "ClockTime = " << runTime.elapsedClockTime() << " s"<< nl << endl;
}

Info<< "End\n" << endl;

return 0;
