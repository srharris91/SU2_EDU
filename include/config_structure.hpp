/*!
 * \file config_structure.hpp
 * \brief All the information about the definition of the physical problem.
 *        The subroutines and functions are in the <i>config_structure.cpp</i> file.
 * \author Aerospace Design Laboratory (Stanford University) <http://su2.stanford.edu>.
 * \version 1.1.0
 *
 * SU2, Copyright (C) 2012-2014 Aerospace Design Laboratory (ADL).
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <cmath>
#include <map>

#include "option_structure.hpp"

using namespace std;

/*! 
 * \class CConfig
 * \brief Main class for defining the problem; basically this class reads the configuration file, and
 *        stores all the information.
 * \author F. Palacios.
 * \version 1.1.0
 */
class CConfig {
private:
	unsigned short Kind_SU2; /*!< \brief Kind of SU2 software component. */
	unsigned short iZone, nZone; /*!< \brief Number of zones in the mesh. */
	double OrderMagResidual; /*!< \brief Order of magnitude reduction. */
	double MinLogResidual; /*!< \brief Minimum value of the log residual. */
	double* EA_IntLimit; /*!< \brief Integration limits of the Equivalent Area computation */
  double AdjointLimit; /*!< \brief Adjoint variable limit */
	double* Hold_GridFixed_Coord; /*!< \brief Coordinates of the box to hold fixed the nbumerical grid */
	unsigned short ConvCriteria;	/*!< \brief Kind of convergence criteria. */
	bool Adjoint,			/*!< \brief Flag to know if the code is solving an adjoint problem. */
    Viscous,                /*!< \brief Flag to know if the code is solving a viscous problem. */
	EquivArea,				/*!< \brief Flag to know if the code is going to compute and plot the equivalent area. */
	OneShot,				/*!< \brief Flag to know if the code is solving a one shot problem. */
	Linearized,				/*!< \brief Flag to know if the code is solving a linearized problem. */
	Grid_Movement,			/*!< \brief Flag to know if there is grid movement. */
	Rotating_Frame,			/*!< \brief Flag to know if there is a rotating frame. */
	PoissonSolver,			/*!< \brief Flag to know if we are solving  poisson forces  in plasma solver. */
	Low_Mach_Precon,		/*!< \brief Flag to know if we are using a low Mach number preconditioner. */
	GravityForce,			/*!< \brief Flag to know if the gravity force is incuded in the formulation. */
	SmoothNumGrid,			/*!< \brief Smooth the numerical grid. */
	AdaptBoundary,			/*!< \brief Adapt the elements on the boundary. */
	FullMG,					/*!< \brief Full multigrid strategy. */
	Divide_Element,			/*!< \brief Divide rectables and hexahedrom. */
	Engine_Intake,			/*!< \brief Engine intake subsonic region. */
	Frozen_Visc,			/*!< \brief Flag for adjoint problem with/without frozen viscosity. */
	Sens_Remove_Sharp,			/*!< \brief Flag for removing or not the sharp edges from the sensitivity computation. */
	Hold_GridFixed,	/*!< \brief Flag hold fixed some part of the mesh during the deformation. */
	Axisymmetric, /*!< \brief Flag for axisymmetric calculations */
	Show_Adj_Sens, /*!< \brief Flag for outputting sensitivities on exit */
  ionization;  /*!< \brief Flag for determining if free electron gas is in the mixture */
	bool Visualize_Partition;	/*!< \brief Flag to visualize each partition in the DDM. */
	bool Visualize_Deformation;	/*!< \brief Flag to visualize the deformation in the MDC. */
    double Damp_Nacelle_Inflow;	/*!< \brief Damping factor for the engine inlet. */
	double Damp_Res_Restric,	/*!< \brief Damping factor for the residual restriction. */
	Damp_Correc_Prolong; /*!< \brief Damping factor for the correction prolongation. */
	double Position_Plane; /*!< \brief Position of the Near-Field (y coordinate 2D, and z coordinate 3D). */
	double WeightCd; /*!< \brief Weight of the drag coefficient. */
	unsigned short Unsteady_Simulation;	/*!< \brief Steady or unsteady (time stepping or dual time stepping) computation. */
	unsigned short nStartUpIter;	/*!< \brief Start up iterations using the fine grid. */
	double CteViscDrag;		/*!< \brief Constant value of the viscous drag. */
	double *DV_Value;		/*!< \brief Previous value of the design variable. */
	double LimiterCoeff;				/*!< \brief Limiter coefficient */ 
	double SharpEdgesCoeff;				/*!< \brief Coefficient to identify the limit of a sharp edge. */
	unsigned short Kind_Regime;	/*!< \brief Kind of adjoint function. */
	unsigned short Kind_ObjFunc;	/*!< \brief Kind of objective function. */
	unsigned short Kind_SensSmooth;	/*!< \brief Kind of sensitivity smoothing technique. */
	unsigned short Continuous_Eqns;	/*!< \brief Which equations to treat continuously (Hybrid adjoint) */
	unsigned short Discrete_Eqns;	/*!< \brief Which equations to treat discretely (Hybrid adjoint). */
	unsigned short *Design_Variable; /*!< \brief Kind of design variable. */
	unsigned short Kind_Adaptation;	/*!< \brief Kind of numerical grid adaptation. */
	unsigned short nTimeInstances;  /*!< \brief Number of periodic time instances for Time Spectral integration. */
	double TimeSpectral_Period;		/*!< \brief Period of oscillation to be used with time-spectral computations. */
	double New_Elem_Adapt;			/*!< \brief Elements to adapt in the numerical grid adaptation process. */
	double Delta_UnstTime,			/*!< \brief Time step for unsteady computations. */
	Delta_UnstTimeND;						/*!< \brief Time step for unsteady computations (non dimensional). */
	double Total_UnstTime,						/*!< \brief Total time for unsteady computations. */
	Total_UnstTimeND;								/*!< \brief Total time for unsteady computations (non dimensional). */
	double Current_UnstTime,									/*!< \brief Global time of the unsteady simulation. */
	Current_UnstTimeND;									/*!< \brief Global time of the unsteady simulation. */
	unsigned short nMarker_Euler,	/*!< \brief Number of Euler wall markers. */
	nMarker_FarField,				/*!< \brief Number of far-field markers. */
	nMarker_Custom,
	nMarker_SymWall,				/*!< \brief Number of symmetry wall markers. */
  nMarker_Pressure,				/*!< \brief Number of pressure wall markers. */
	nMarker_PerBound,				/*!< \brief Number of periodic boundary markers. */
	nMarker_NearFieldBound,				/*!< \brief Number of near field boundary markers. */
	nMarker_InterfaceBound,				/*!< \brief Number of interface boundary markers. */
	nMarker_Dirichlet,				/*!< \brief Number of interface boundary markers. */
	nMarker_Dirichlet_Elec,				/*!< \brief Number of interface boundary markers. */
	nMarker_Inlet,					/*!< \brief Number of inlet flow markers. */
	nMarker_Supersonic_Inlet,					/*!< \brief Number of supersonic inlet flow markers. */
	nMarker_Outlet,					/*!< \brief Number of outlet flow markers. */
	nMarker_Isothermal,     /*!< \brief Number of isothermal wall boundaries. */
	nMarker_HeatFlux,       /*!< \brief Number of constant heat flux wall boundaries. */
	nMarker_NacelleExhaust,					/*!< \brief Number of nacelle exhaust flow markers. */
	nMarker_NacelleInflow,					/*!< \brief Number of nacelle inflow flow markers. */
	nMarker_Displacement,					/*!< \brief Number of displacement surface markers. */
	nMarker_Load,					/*!< \brief Number of load surface markers. */
	nMarker_FlowLoad,					/*!< \brief Number of load surface markers. */
	nMarker_Neumann,				/*!< \brief Number of Neumann flow markers. */
	nMarker_Neumann_Elec,				/*!< \brief Number of Neumann flow markers. */
	nMarker_All,					/*!< \brief Total number of markers using the grid information. */
	nMarker_Config;					/*!< \brief Total number of markers using the config file 
									(note that using parallel computation this number can be different 
									from nMarker_All). */
	string *Marker_Euler,			/*!< \brief Euler wall markers. */
	*Marker_FarField,				/*!< \brief Far field markers. */
	*Marker_Custom,
	*Marker_SymWall,				/*!< \brief Symmetry wall markers. */
  *Marker_Pressure,				/*!< \brief Pressure boundary markers. */
	*Marker_PerBound,				/*!< \brief Periodic boundary markers. */
	*Marker_PerDonor,				/*!< \brief Rotationally periodic boundary donor markers. */
	*Marker_NearFieldBound,				/*!< \brief Near Field boundaries markers. */
	*Marker_InterfaceBound,				/*!< \brief Interface boundaries markers. */
	*Marker_Dirichlet,				/*!< \brief Interface boundaries markers. */
	*Marker_Dirichlet_Elec,				/*!< \brief Interface boundaries markers. */
	*Marker_Inlet,					/*!< \brief Inlet flow markers. */
	*Marker_Supersonic_Inlet,					/*!< \brief Supersonic inlet flow markers. */
	*Marker_Outlet,					/*!< \brief Outlet flow markers. */
	*Marker_Isothermal,     /*!< \brief Isothermal wall markers. */
	*Marker_HeatFlux,       /*!< \brief Constant heat flux wall markers. */
	*Marker_NacelleInflow,					/*!< \brief Nacelle Inflow flow markers. */
	*Marker_NacelleExhaust,					/*!< \brief Nacelle Exhaust flow markers. */
	*Marker_Displacement,					/*!< \brief Displacement markers. */
	*Marker_Load,					/*!< \brief Load markers. */
	*Marker_FlowLoad,					/*!< \brief Flow Load markers. */
	*Marker_Neumann,					/*!< \brief Neumann flow markers. */
	*Marker_Neumann_Elec,					/*!< \brief Neumann flow markers. */
	*Marker_All_Tag;				/*!< \brief Global index for markers using grid information. */
	double *Dirichlet_Value;    /*!< \brief Specified Dirichlet value at the boundaries. */
	double *Nozzle_Ttotal;    /*!< \brief Specified total temperatures for nacelle boundaries. */
	double *Nozzle_Ptotal;    /*!< \brief Specified total pressures for nacelle boundaries. */
	double *Inlet_Ttotal;    /*!< \brief Specified total temperatures for inlet boundaries. */
	double *Inlet_Ptotal;    /*!< \brief Specified total pressures for inlet boundaries. */
	double **Inlet_FlowDir;  /*!< \brief Specified flow direction vector (unit vector) for inlet boundaries. */
	double *Inlet_Temperature;    /*!< \brief Specified temperatures for a supersonic inlet boundaries. */
	double *Inlet_Pressure;    /*!< \brief Specified static pressures for supersonic inlet boundaries. */
	double **Inlet_Velocity;  /*!< \brief Specified flow velocity vectors for supersonic inlet boundaries. */
	double *FanFace_Mach_Target;    /*!< \brief Specified fan face mach for nacelle boundaries. */
	double *FanFace_Mach;    /*!< \brief Specified fan face mach for nacelle boundaries. */
	double *FanFace_Pressure;    /*!< \brief Specified fan face mach for nacelle boundaries. */
    double *Outlet_Pressure;    /*!< \brief Specified back pressures (static) for outlet boundaries. */
	double *Isothermal_Temperature; /*!< \brief Specified isothermal wall temperatures (static). */
	double *Heat_Flux;  /*!< \brief Specified wall heat fluxes. */
	double *Displ_Value;    /*!< \brief Specified displacement for displacement boundaries. */
	double *Load_Value;    /*!< \brief Specified force for load boundaries. */
	double *FlowLoad_Value;    /*!< \brief Specified force for flow load boundaries. */
	double **Periodic_RotCenter;  /*!< \brief Rotational center for each periodic boundary. */
	double **Periodic_RotAngles;      /*!< \brief Rotation angles for each periodic boundary. */
	double **Periodic_Translation;      /*!< \brief Translation vector for each periodic boundary. */
	unsigned short nPeriodic_Index;     /*!< \brief Number of SEND_RECEIVE periodic transformations. */
	double **Periodic_Center;         /*!< \brief Rotational center for each SEND_RECEIVE boundary. */
	double **Periodic_Rotation;      /*!< \brief Rotation angles for each SEND_RECEIVE boundary. */
	double **Periodic_Translate;      /*!< \brief Translation vector for each SEND_RECEIVE boundary. */
	string *Marker_Config_Tag;			/*!< \brief Global index for markers using config file. */
	unsigned short *Marker_All_Boundary,			/*!< \brief Global index for boundaries using grid information. */
	*Marker_Config_Boundary;		/*!< \brief Global index for boundaries using config file. */
	short *Marker_All_SendRecv;		/*!< \brief Information about if the boundary is sended (+), received (-). */
	short *Marker_All_PerBound;	/*!< \brief Global index for periodic bc using the grid information. */
	unsigned long nExtIter;			/*!< \brief Number of external iterations. */
	unsigned long ExtIter;			/*!< \brief Current external iteration number. */
	unsigned long IntIter;			/*!< \brief Current internal iteration number. */
	unsigned long Unst_nIntIter;			/*!< \brief Number of internal iterations (Dual time Method). */
  long Unst_RestartIter;			/*!< \brief Iteration number to restart an unsteady simulation (Dual time Method). */
  long Unst_AdjointIter;			/*!< \brief Iteration number to begin the reverse time integration in the direct solver for the unsteady adjoint. */
	unsigned short nRKStep;			/*!< \brief Number of steps of the explicit Runge-Kutta method. */
	double *RK_Alpha_Step;			/*!< \brief Runge-Kutta beta coefficients. */
	unsigned short nMultiLevel;		/*!< \brief Number of multigrid levels (coarse levels). */
	unsigned short nCFL;			/*!< \brief Number of CFL, one for each multigrid level. */
	double
	MG_CFLRedCoeff,		/*!< \brief CFL reduction coefficient on the MG coarse level. */
	Turb_CFLRedCoeff,		/*!< \brief CFL reduction coefficient on the LevelSet problem. */
	Adj_CFLRedCoeff,	/*!< \brief CFL reduction coefficient for the adjoint problem. */
	AdjTurb_CFLRedCoeff,	/*!< \brief CFL reduction coefficient for the adjoint problem. */
	CFLFineGrid,		/*!< \brief CFL of the finest grid. */
	Unst_CFL;		/*!< \brief Unsteady CFL number. */
	unsigned short MaxChildren;		/*!< \brief Maximum number of children. */
	double MaxDimension;			/*!< \brief Maximum dimension of the aglomerated element compared with the whole domain. */
	bool AddIndNeighbor;			/*!< \brief Include indirect neighbor in the agglomeration process. */
	unsigned short nDV;		/*!< \brief Number of design variables. */
  unsigned short nGridMovement;		/*!< \brief Number of grid movement types specified. */
	unsigned short nParamDV;		/*!< \brief Number of parameters of the design variable. */
	double **ParamDV;				/*!< \brief Parameters of the design variable. */
	unsigned short GeometryMode;			/*!< \brief Gemoetry mode (analysis or gradient computation). */
	unsigned short MGCycle;			/*!< \brief Kind of multigrid cycle. */
	unsigned short FinestMesh;		/*!< \brief Finest mesh for the full multigrid approach. */
	unsigned short nMG_PreSmooth,                 /*!< \brief Number of MG pre-smooth parameters found in config file. */
	nMG_PostSmooth,                             /*!< \brief Number of MG post-smooth parameters found in config file. */
	nMG_CorrecSmooth;                           /*!< \brief Number of MG correct-smooth parameters found in config file. */
	unsigned short *MG_PreSmooth,	/*!< \brief Multigrid Pre smoothing. */
	*MG_PostSmooth,					/*!< \brief Multigrid Post smoothing. */
	*MG_CorrecSmooth;					/*!< \brief Multigrid Jacobi implicit smoothing of the correction. */
	unsigned short Kind_Solver,	/*!< \brief Kind of solver Euler, NS, Continuous adjoint, etc. */
	Kind_GasModel,				/*!< \brief Kind of the Gas Model. */
	*Kind_GridMovement,    /*!< \brief Kind of the unsteady mesh movement. */
	Kind_Gradient_Method,		/*!< \brief Numerical method for computation of spatial gradients. */
	Kind_Linear_Solver,		/*!< \brief Numerical solver for the implicit scheme. */
	Kind_Linear_Solver_Prec,		/*!< \brief Preconditioner of the linear solver. */
	Kind_AdjTurb_Linear_Solver,		/*!< \brief Numerical solver for the turbulent adjoint implicit scheme. */
	Kind_AdjTurb_Linear_Prec,		/*!< \brief Preconditioner of the turbulent adjoint linear solver. */
	Kind_SlopeLimit,				/*!< \brief Global slope limiter. */
	Kind_SlopeLimit_Flow,		/*!< \brief Slope limiter for flow equations.*/
	Kind_SlopeLimit_TNE2,		/*!< \brief Slope limiter for flow equations.*/
  Kind_SlopeLimit_AdjTNE2,		/*!< \brief Slope limiter for flow equations.*/
	Kind_SlopeLimit_Turb,		/*!< \brief Slope limiter for the turbulence equation.*/
	Kind_SlopeLimit_AdjLevelSet,		/*!< \brief Slope limiter for the adjoint level set equation.*/
	Kind_SlopeLimit_AdjTurb,	/*!< \brief Slope limiter for the adjoint turbulent equation.*/
	Kind_SlopeLimit_AdjFlow,	/*!< \brief Slope limiter for the adjoint equation.*/
	Kind_TimeNumScheme,			/*!< \brief Global explicit or implicit time integration. */
	Kind_TimeIntScheme_Flow,	/*!< \brief Time integration for the flow equations. */
	Kind_TimeIntScheme_AdjFlow,		/*!< \brief Time integration for the adjoint flow equations. */
  Kind_TimeIntScheme_TNE2,	/*!< \brief Time integration for the flow equations. */
  Kind_TimeIntScheme_AdjTNE2, /*!< \brief Time integration for the flow equations. */
	Kind_TimeIntScheme_LinFlow,		/*!< \brief Time integration for the linearized flow equations. */
	Kind_TimeIntScheme_Turb,	/*!< \brief Time integration for the turbulence model. */
	Kind_TimeIntScheme_AdjLevelSet,	/*!< \brief Time integration for the adjoint level set model. */
	Kind_TimeIntScheme_AdjTurb,	/*!< \brief Time integration for the adjoint turbulence model. */
	Kind_TimeIntScheme_Wave,	/*!< \brief Time integration for the wave equations. */
	Kind_TimeIntScheme_Heat,	/*!< \brief Time integration for the wave equations. */
	Kind_TimeIntScheme_Poisson,	/*!< \brief Time integration for the wave equations. */
	Kind_TimeIntScheme_FEA,	/*!< \brief Time integration for the FEA equations. */
	Kind_ConvNumScheme,			/*!< \brief Global definition of the convective term. */
	Kind_ConvNumScheme_Flow,	/*!< \brief Centered or upwind scheme for the flow equations. */
	Kind_ConvNumScheme_Heat,	/*!< \brief Centered or upwind scheme for the flow equations. */
	Kind_ConvNumScheme_TNE2,	/*!< \brief Centered or upwind scheme for the flow equations. */
	Kind_ConvNumScheme_AdjFlow,		/*!< \brief Centered or upwind scheme for the adjoint flow equations. */
  Kind_ConvNumScheme_AdjTNE2,		/*!< \brief Centered or upwind scheme for the adjoint TNE2 equations. */
	Kind_ConvNumScheme_LinFlow,		/*!< \brief Centered or upwind scheme for the linearized flow equations. */
	Kind_ConvNumScheme_Turb,	/*!< \brief Centered or upwind scheme for the turbulence model. */
	Kind_ConvNumScheme_AdjTurb,	/*!< \brief Centered or upwind scheme for the adjoint turbulence model. */
	Kind_ConvNumScheme_AdjLevelSet,	/*!< \brief Centered or upwind scheme for the adjoint level set equation. */
	Kind_ConvNumScheme_Template,	/*!< \brief Centered or upwind scheme for the level set equation. */
	Kind_ViscNumScheme,			/*!< \brief Global definition of the viscous term. */
	Kind_ViscNumScheme_Flow,	/*!< \brief Viscous scheme for the flow equations. */
	Kind_ViscNumScheme_Heat,	/*!< \brief Viscous scheme for the flow equations. */
	Kind_ViscNumScheme_AdjFlow,		/*!< \brief Viscous scheme for the adjoint flow equations. */
  Kind_ViscNumScheme_TNE2,	/*!< \brief Viscous scheme for the flow equations. */
  Kind_ViscNumScheme_AdjTNE2, /*!< \brief Viscous scheme for the flow equations. */
	Kind_ViscNumScheme_LinFlow,		/*!< \brief Viscous scheme for the linearized flow equations. */
	Kind_ViscNumScheme_Turb,	/*!< \brief Viscous scheme for the turbulence model. */
	Kind_ViscNumScheme_Poisson,	/*!< \brief Viscous scheme for the poisson potential. */
	Kind_ViscNumScheme_Wave,	/*!< \brief Viscous scheme for the wave equation. */
	Kind_ViscNumScheme_FEA,	/*!< \brief Viscous scheme for the FEA equation. */
	Kind_ViscNumScheme_AdjTurb,	/*!< \brief Viscous scheme for the adjoint turbulence model. */
	Kind_ViscNumScheme_AdjLevelSet,	/*!< \brief Viscous scheme for the adjoint level set equation. */
	Kind_ViscNumScheme_Template,	/*!< \brief Viscous scheme for the template. */
	Kind_SourNumScheme,			/*!< \brief Global definition of the source term. */
	Kind_SourNumScheme_Flow,	/*!< \brief Source numerical scheme for the flow equations. */
	Kind_SourNumScheme_Heat,	/*!< \brief Source numerical scheme for the flow equations. */
	Kind_SourNumScheme_AdjFlow,		/*!< \brief Source numerical scheme for the adjoint flow equations. */
  Kind_SourNumScheme_TNE2,	/*!< \brief Source numerical scheme for the flow equations. */
  Kind_SourNumScheme_AdjTNE2,	/*!< \brief Source numerical scheme for the flow equations. */
	Kind_SourNumScheme_LinFlow,		/*!< \brief Source numerical scheme for the linearized flow equations. */
	Kind_SourNumScheme_Turb,	/*!< \brief Source numerical scheme for the turbulence model. */
	Kind_SourNumScheme_Poisson,	/*!< \brief Source numerical scheme for the poisson potential. */
	Kind_SourNumScheme_AdjTurb,	/*!< \brief Source numerical scheme for the adjoint turbulence model. */
	Kind_SourNumScheme_AdjLevelSet,	/*!< \brief Source numerical scheme for the adjoint level set model. */
	Kind_SourNumScheme_LevelSet,	/*!< \brief Source scheme for the level set equation. */
	Kind_SourNumScheme_Wave,	/*!< \brief Source scheme for the wave equation. */
	Kind_SourNumScheme_FEA,	/*!< \brief Source scheme for the FEA equation. */
	Kind_SourNumScheme_Template,	/*!< \brief Source numerical scheme for the template. */
	Kind_Centered,				/*!< \brief Centered scheme. */
	Kind_Centered_Flow,			/*!< \brief Centered scheme for the flow equations. */
	Kind_Centered_TNE2,			/*!< \brief Centered scheme for the flow equations. */
	Kind_Centered_AdjLevelSet,			/*!< \brief Centered scheme for the level set equation. */
	Kind_Centered_AdjFlow,			/*!< \brief Centered scheme for the adjoint flow equations. */
  Kind_Centered_AdjTNE2,			/*!< \brief Centered scheme for the adjoint TNE2 equations. */
	Kind_Centered_LinFlow,			/*!< \brief Centered scheme for the linearized flow equations. */
	Kind_Centered_Turb,			/*!< \brief Centered scheme for the turbulence model. */
	Kind_Centered_AdjTurb,		/*!< \brief Centered scheme for the adjoint turbulence model. */
	Kind_Centered_Template,		/*!< \brief Centered scheme for the template model. */
	Kind_Upwind,				/*!< \brief Upwind scheme. */
	Kind_Upwind_Flow,			/*!< \brief Upwind scheme for the flow equations. */
	Kind_Upwind_TNE2,			/*!< \brief Upwind scheme for the flow equations. */
	Kind_Upwind_AdjLevelSet,			/*!< \brief Upwind scheme for the level set equations. */
	Kind_Upwind_AdjFlow,			/*!< \brief Upwind scheme for the adjoint flow equations. */
  Kind_Upwind_AdjTNE2,			/*!< \brief Upwind scheme for the adjoint TNE2 equations. */
	Kind_Upwind_LinFlow,			/*!< \brief Upwind scheme for the linearized flow equations. */
	Kind_Upwind_Turb,			/*!< \brief Upwind scheme for the turbulence model. */
	Kind_Upwind_AdjTurb,		/*!< \brief Upwind scheme for the adjoint turbulence model. */
	Kind_Upwind_Template;			/*!< \brief Upwind scheme for the template model. */
  unsigned short Kind_Turb_Model;			/*!< \brief Turbulent model definition. */
  string ML_Turb_Model_File;  /*!< \brief File containing turbulence model. */
  string ML_Turb_Model_Check_File; /*!< \brief File containing turbulence model check (to confirm it was loaded properly) */
  
  unsigned short Kind_Trans_Model,			/*!< \brief Transition model definition. */
	Kind_Inlet;           /*!< \brief Kind of inlet boundary treatment. */
	double Linear_Solver_Error;		/*!< \brief Min error of the linear solver for the implicit formulation. */
	unsigned long Linear_Solver_Iter;		/*!< \brief Min error of the linear solver for the implicit formulation. */
	double Linear_Solver_Relax;		/*!< \brief Relaxation coefficient of the linear solver. */
	double AdjTurb_Linear_Error;		/*!< \brief Min error of the turbulent adjoint linear solver for the implicit formulation. */
	unsigned short AdjTurb_Linear_Iter;		/*!< \brief Min error of the turbulent adjoint linear solver for the implicit formulation. */
	double *Section_Limit;                  /*!< \brief Airfoil section limit. */
	double* Kappa_Flow,           /*!< \brief Numerical dissipation coefficients for the flow equations. */
	*Kappa_AdjFlow,                  /*!< \brief Numerical dissipation coefficients for the adjoint equations. */
  *Kappa_TNE2,             /*!< \brief Numerical dissipation coefficients for the TNE2 equations. */
  *Kappa_AdjTNE2,          /*!< \brief Numerical dissipation coefficients for the adjoint TNE2 equations. */
	*Kappa_LinFlow;                  /*!< \brief Numerical dissipation coefficients for the linearized equations. */
	double Kappa_1st_AdjFlow,	/*!< \brief JST 1st order dissipation coefficient for adjoint flow equations (coarse multigrid levels). */
	Kappa_2nd_AdjFlow,			/*!< \brief JST 2nd order dissipation coefficient for adjoint flow equations. */
	Kappa_4th_AdjFlow,			/*!< \brief JST 4th order dissipation coefficient for adjoint flow equations. */
	Kappa_1st_LinFlow,			/*!< \brief JST 1st order dissipation coefficient for linearized flow equations (coarse multigrid levels). */
	Kappa_4th_LinFlow,			/*!< \brief JST 4th order dissipation coefficient for linearized flow equations. */
	Kappa_1st_Flow,			/*!< \brief JST 1st order dissipation coefficient for flow equations (coarse multigrid levels). */
	Kappa_2nd_Flow,			/*!< \brief JST 2nd order dissipation coefficient for flow equations. */
	Kappa_4th_Flow,			/*!< \brief JST 4th order dissipation coefficient for flow equations. */
	Kappa_1st_TNE2,			/*!< \brief JST 1st order dissipation coefficient for flow equations (coarse multigrid levels). */
	Kappa_2nd_TNE2,			/*!< \brief JST 2nd order dissipation coefficient for flow equations. */
	Kappa_4th_TNE2,			/*!< \brief JST 4th order dissipation coefficient for flow equations. */
  Kappa_1st_AdjTNE2,			/*!< \brief JST 1st order dissipation coefficient for flow equations (coarse multigrid levels). */
	Kappa_2nd_AdjTNE2,			/*!< \brief JST 2nd order dissipation coefficient for flow equations. */
	Kappa_4th_AdjTNE2;			/*!< \brief JST 4th order dissipation coefficient for flow equations. */

	double Min_Beta_RoeTurkel,		/*!< \brief Minimum value of Beta for the Roe-Turkel low Mach preconditioner. */
	Max_Beta_RoeTurkel;		/*!< \brief Maximum value of Beta for the Roe-Turkel low Mach preconditioner. */
  unsigned long GridDef_Iter; /*!< \brief Number of incrememts for grid deformation. */
	double Mach;		/*!< \brief Mach number. */
	double Reynolds;	/*!< \brief Reynolds number. */
	double Froude;	/*!< \brief Froude number. */	
	double Length_Reynolds;	/*!< \brief Reynolds length (dimensional). */
	double AoA,			/*!< \brief Angle of attack (just external flow). */
	AoS;				/*!< \brief Angle of sideSlip (just external flow). */
	double ChargeCoeff;		/*!< \brief Charge coefficient (just for poisson problems). */
	double *U_FreeStreamND;			/*!< \brief Reference variables at the infinity, free stream values. */ 
	unsigned short Cauchy_Func_Flow,	/*!< \brief Function where to apply the convergence criteria in the flow problem. */
	Cauchy_Func_AdjFlow,				/*!< \brief Function where to apply the convergence criteria in the adjoint problem. */
	Cauchy_Func_LinFlow,				/*!< \brief Function where to apply the convergence criteria in the linearized problem. */
	Cauchy_Elems;						/*!< \brief Number of elements to evaluate. */
	unsigned long StartConv_Iter;	/*!< \brief Start convergence criteria at iteration. */
	double Cauchy_Eps,	/*!< \brief Epsilon used for the convergence. */
	Cauchy_Eps_OneShot,	/*!< \brief Epsilon used for the one shot method convergence. */
	Cauchy_Eps_FullMG;	/*!< \brief Epsilon used for the full multigrid method convergence. */
	unsigned long Wrt_Sol_Freq,	/*!< \brief Writing solution frequency. */
	Wrt_Sol_Freq_DualTime,	/*!< \brief Writing solution frequency for Dual Time. */
	Wrt_Con_Freq,				/*!< \brief Writing convergence history frequency. */
	Wrt_Con_Freq_DualTime;				/*!< \brief Writing convergence history frequency. */
	bool Wrt_Unsteady;  /*!< \brief Write unsteady data adding header and prefix. */
	bool Restart,	/*!< \brief Restart solution (for direct, adjoint, and linearized problems). */
	Restart_Flow;	/*!< \brief Restart flow solution for adjoint and linearized problems. */
	unsigned short nMarker_Monitoring,	/*!< \brief Number of markers to monitor. */
	nMarker_Designing,					/*!< \brief Number of markers for the objective function. */
	nMarker_Plotting,					/*!< \brief Number of markers to plot. */
  nMarker_Moving,               /*!< \brief Number of markers in motion (DEFORMING, MOVING_WALL, or FLUID_STRUCTURE). */
	nMarker_DV;               /*!< \brief Number of markers affected by the design variables. */
	string *Marker_Monitoring,			/*!< \brief Markers to monitor. */
	*Marker_Designing,					/*!< \brief Markers to plot. */
	*Marker_Plotting,					/*!< \brief Markers to plot. */
  *Marker_Moving,						/*!< \brief Markers in motion (DEFORMING, MOVING_WALL, or FLUID_STRUCTURE). */
	*Marker_DV;						/*!< \brief Markers affected by the design variables. */
	unsigned short  *Marker_All_Monitoring,				/*!< \brief Global index for monitoring using the grid information. */
	*Marker_All_Plotting,				/*!< \brief Global index for plotting using the grid information. */
	*Marker_All_DV,					/*!< \brief Global index for design variable markers using the grid information. */
  *Marker_All_Moving,					/*!< \brief Global index for moving surfaces using the grid information. */
	*Marker_All_Designing,					/*!< \brief Global index for moving using the grid information. */
	*Marker_Config_Monitoring,			/*!< \brief Global index for monitoring using the config information. */
	*Marker_Config_Designing,			/*!< \brief Global index for monitoring using the config information. */
	*Marker_Config_Plotting,			/*!< \brief Global index for plotting using the config information. */
  *Marker_Config_Moving,				/*!< \brief Global index for moving surfaces using the config information. */
	*Marker_Config_DV,				/*!< \brief Global index for design variable markers using the config information. */
	*Marker_Config_PerBound;			/*!< \brief Global index for periodic boundaries using the config information. */
	string *PlaneTag;			/*!< \brief Global index for the plane adaptation (upper, lower). */
	unsigned short nDomain;			/*!< \brief Number of domains in the MPI parallelization. */
	double DualVol_Power;			/*!< \brief Power for the dual volume in the grid adaptation sensor. */
	unsigned short Analytical_Surface;	/*!< \brief Information about the analytical definition of the surface for grid adaptation. */
	unsigned short Mesh_FileFormat;	/*!< \brief Mesh input format. */
	unsigned short Output_FileFormat;	/*!< \brief Format of the output files. */
	double RefAreaCoeff,		/*!< \brief Reference area for coefficient computation. */
	RefElemLength,				/*!< \brief Reference element length for computing the slope limiting epsilon. */
	RefSharpEdges,				/*!< \brief Reference coefficient for detecting sharp edges. */
	RefLengthMoment,			/*!< \brief Reference length for moment computation. */
  *RefOriginMoment,           /*!< \brief Origin for moment computation. */
	*RefOriginMoment_X,			/*!< \brief X Origin for moment computation. */
  *RefOriginMoment_Y,			/*!< \brief Y Origin for moment computation. */
	*RefOriginMoment_Z,			/*!< \brief Z Origin for moment computation. */
	*CFLRamp,			/*!< \brief Information about the CFL ramp. */
  *CFL,
	DomainVolume;		/*!< \brief Volume of the computational grid. */
  unsigned short nRefOriginMoment_X,    /*!< \brief Number of X-coordinate moment computation origins. */
	nRefOriginMoment_Y,           /*!< \brief Number of Y-coordinate moment computation origins. */
	nRefOriginMoment_Z;           /*!< \brief Number of Z-coordinate moment computation origins. */
	string Mesh_FileName,			/*!< \brief Mesh input file. */
	Mesh_Out_FileName,				/*!< \brief Mesh output file. */
	Solution_FlowFileName,			/*!< \brief Flow solution input file. */
	Solution_LinFileName,			/*!< \brief Linearized flow solution input file. */
	Solution_AdjFileName,			/*!< \brief Adjoint solution input file for drag functional. */
	Flow_FileName,					/*!< \brief Flow variables output file. */
	Structure_FileName,					/*!< \brief Structure variables output file. */
	SurfStructure_FileName,					/*!< \brief Surface structure variables output file. */
  SurfWave_FileName,					/*!< \brief Surface structure variables output file. */
	SurfHeat_FileName,					/*!< \brief Surface structure variables output file. */
	Wave_FileName,					/*!< \brief Wave variables output file. */
	Heat_FileName,					/*!< \brief Heat variables output file. */
	AdjWave_FileName,					/*!< \brief Adjoint wave variables output file. */
	Residual_FileName,				/*!< \brief Residual variables output file. */
	Conv_FileName,					/*!< \brief Convergence history output file. */
	Restart_FlowFileName,			/*!< \brief Restart file for flow variables. */
	Restart_WaveFileName,			/*!< \brief Restart file for wave variables. */
	Restart_HeatFileName,			/*!< \brief Restart file for heat variables. */
	Restart_LinFileName,			/*!< \brief Restart file for linearized flow variables. */
	Restart_AdjFileName,			/*!< \brief Restart file for adjoint variables, drag functional. */
	Adj_FileName,					/*!< \brief Output file with the adjoint variables. */
	Lin_FileName,					/*!< \brief Output file with the linearized variables. */
	ObjFunc_Grad_FileName,			/*!< \brief Gradient of the objective function. */
	ObjFunc_Value_FileName,			/*!< \brief Objective function. */
	SurfFlowCoeff_FileName,			/*!< \brief Output file with the flow variables on the surface. */
	SurfAdjCoeff_FileName,			/*!< \brief Output file with the adjoint variables on the surface. */
	SurfLinCoeff_FileName,			/*!< \brief Output file with the linearized variables on the surface. */
	New_SU2_FileName;        		/*!< \brief Output SU2 mesh file converted from CGNS format. */
	bool CGNS_To_SU2;      		 	/*!< \brief Flag to specify whether a CGNS mesh is converted to SU2 format. */
	bool Wrt_Vol_Sol,                /*!< \brief Write a volume solution file */
	Wrt_Srf_Sol,                /*!< \brief Write a surface solution file */
	Wrt_Restart,                /*!< \brief Write a restart solution file */
	Wrt_Csv_Sol,                /*!< \brief Write a surface comma-separated values solution file */
	Wrt_Residuals,              /*!< \brief Write residuals to solution file */
  Wrt_Halo,                   /*!< \brief Write rind layers in solution files */
  Wrt_Sectional_Forces;       /*!< \brief Write sectional forces for specified markers. */
	bool Inlet_Outlet_Defined; /*!< \brief  that inlet and outlet conditions are defined for each species*/
	double Gamma,			/*!< \brief Ratio of specific heats of the gas. */
	Bulk_Modulus,			/*!< \brief Value of the bulk modulus for incompressible flows. */ 
	ArtComp_Factor,			/*!< \brief Value of the artificial compresibility factor for incompressible flows. */
	Gas_Constant,     /*!< \brief Specific gas constant. */
	Gas_ConstantND,     /*!< \brief Non-dimensional specific gas constant. */
	Gas_Constant_Ref, /*!< \brief Reference specific gas constant. */
	*Velocity_FreeStream,     /*!< \brief Total velocity of the fluid.  */
	Density_FreeStream,     /*!< \brief Total density of the fluid.  */
	Viscosity_FreeStream,     /*!< \brief Total density of the fluid.  */
	Intermittency_FreeStream,     /*!< \brief Freestream intermittency (for sagt transition model) of the fluid.  */
	TurbulenceIntensity_FreeStream,     /*!< \brief Freestream turbulent intensity (for sagt transition model) of the fluid.  */
	Turb2LamViscRatio_FreeStream,          /*!< \brief Ratio of turbulent to laminar viscosity. */
	NuFactor_FreeStream,  /*!< \brief Ratio of turbulent to laminar viscosity. */
	Pressure_FreeStream,     /*!< \brief Total pressure of the fluid.  */
	Temperature_FreeStream,  /*!< \brief Total temperature of the fluid.  */
  Temperature_ve_FreeStream,  /*!< \brief Total vibrational-electronic temperature of the fluid.  */
  *MassFrac_FreeStream, /*!< \brief Mixture mass fractions of the fluid. */
	Prandtl_Lam,      /*!< \brief Laminar Prandtl number for the gas.  */
	Prandtl_Turb,     /*!< \brief Turbulent Prandtl number for the gas.  */
	Length_Ref,       /*!< \brief Reference length for non-dimensionalization. */
	Conversion_Factor,       /*!< \brief Conversion factor from grid units to meters. */
	Pressure_Ref,     /*!< \brief Reference pressure for non-dimensionalization. */
	Temperature_Ref,  /*!< \brief Reference temperature for non-dimensionalization. */
	Density_Ref,      /*!< \brief Reference density for non-dimensionalization. */
	Velocity_Ref,     /*!< \brief Reference velocity for non-dimensionalization. */
	Time_Ref,         /*!< \brief Reference time for non-dimensionalization. */
	Viscosity_Ref,    /*!< \brief Reference viscosity for non-dimensionalization. */
	Wall_Temperature,    /*!< \brief Temperature at an isotropic wall in Kelvin. */
	Omega_Ref,        /*!< \brief Reference angular velocity for non-dimensionalization. */
	Force_Ref,        /*!< \brief Reference body force for non-dimensionalization. */
	Pressure_FreeStreamND,     /*!< \brief Farfield pressure value (external flow). */
	Temperature_FreeStreamND,  /*!< \brief Farfield temperature value (external flow). */
	Density_FreeStreamND,      /*!< \brief Farfield density value (external flow). */
	*Velocity_FreeStreamND,    /*!< \brief Farfield velocity values (external flow). */
	Energy_FreeStreamND,       /*!< \brief Farfield energy value (external flow). */
	Viscosity_FreeStreamND;    /*!< \brief Farfield viscosity value (external flow). */
	bool Write_Converted_Mesh; /*!< \brief Flag to specify whether a new mesh should be written in the converted units. */
	double ElasticyMod,			/*!< \brief Young's modulus of elasticity. */
	PoissonRatio,						/*!< \brief Poisson's ratio. */
	MaterialDensity;								/*!< \brief Material density. */
	double Wave_Speed;			/*!< \brief Wave speed used in the wave solver. */
	double Thermal_Diffusivity;			/*!< \brief Thermal diffusivity used in the heat solver. */
	double Cyclic_Pitch,          /*!< \brief Cyclic pitch for rotorcraft simulations. */
	Collective_Pitch;             /*!< \brief Collective pitch for rotorcraft simulations. */
	string Motion_Filename;				/*!< \brief Arbitrary mesh motion input base filename. */
	double Mach_Motion;			/*!< \brief Mach number based on mesh velocity and freestream quantities. */
	double *Motion_Origin_X,    /*!< \brief X-coordinate of the mesh motion origin. */
	*Motion_Origin_Y,           /*!< \brief Y-coordinate of the mesh motion origin. */
	*Motion_Origin_Z,           /*!< \brief Z-coordinate of the mesh motion origin. */
	*Translation_Rate_X,           /*!< \brief Translational velocity of the mesh in the x-direction. */
	*Translation_Rate_Y,           /*!< \brief Translational velocity of the mesh in the y-direction. */
	*Translation_Rate_Z,           /*!< \brief Translational velocity of the mesh in the z-direction. */
	*Rotation_Rate_X,           /*!< \brief Angular velocity of the mesh about the x-axis. */
	*Rotation_Rate_Y,           /*!< \brief Angular velocity of the mesh about the y-axis. */
	*Rotation_Rate_Z,           /*!< \brief Angular velocity of the mesh about the z-axis. */
	*Pitching_Omega_X,           /*!< \brief Angular frequency of the mesh pitching about the x-axis. */
	*Pitching_Omega_Y,           /*!< \brief Angular frequency of the mesh pitching about the y-axis. */
	*Pitching_Omega_Z,           /*!< \brief Angular frequency of the mesh pitching about the z-axis. */
	*Pitching_Ampl_X,           /*!< \brief Pitching amplitude about the x-axis. */
	*Pitching_Ampl_Y,           /*!< \brief Pitching amplitude about the y-axis. */
	*Pitching_Ampl_Z,           /*!< \brief Pitching amplitude about the z-axis. */
	*Pitching_Phase_X,           /*!< \brief Pitching phase offset about the x-axis. */
	*Pitching_Phase_Y,           /*!< \brief Pitching phase offset about the y-axis. */
	*Pitching_Phase_Z,           /*!< \brief Pitching phase offset about the z-axis. */
	*Plunging_Omega_X,           /*!< \brief Angular frequency of the mesh plunging in the x-direction. */
	*Plunging_Omega_Y,           /*!< \brief Angular frequency of the mesh plunging in the y-direction. */
	*Plunging_Omega_Z,           /*!< \brief Angular frequency of the mesh plunging in the z-direction. */
	*Plunging_Ampl_X,           /*!< \brief Plunging amplitude in the x-direction. */
	*Plunging_Ampl_Y,           /*!< \brief Plunging amplitude in the y-direction. */
	*Plunging_Ampl_Z;           /*!< \brief Plunging amplitude in the z-direction. */
  unsigned short nMotion_Origin_X,    /*!< \brief Number of X-coordinate mesh motion origins. */
	nMotion_Origin_Y,           /*!< \brief Number of Y-coordinate mesh motion origins. */
	nMotion_Origin_Z,           /*!< \brief Number of Z-coordinate mesh motion origins. */
	nTranslation_Rate_X,           /*!< \brief Number of Translational x-velocities for mesh motion. */
	nTranslation_Rate_Y,           /*!< \brief Number of Translational y-velocities for mesh motion. */
	nTranslation_Rate_Z,           /*!< \brief Number of Translational z-velocities for mesh motion. */
	nRotation_Rate_X,           /*!< \brief Number of Angular velocities about the x-axis for mesh motion. */
	nRotation_Rate_Y,           /*!< \brief Number of Angular velocities about the y-axis for mesh motion. */
	nRotation_Rate_Z,           /*!< \brief Number of Angular velocities about the z-axis for mesh motion. */
	nPitching_Omega_X,           /*!< \brief Number of Angular frequencies about the x-axis for pitching. */
	nPitching_Omega_Y,           /*!< \brief Number of Angular frequencies about the y-axis for pitching. */
	nPitching_Omega_Z,           /*!< \brief Number of Angular frequencies about the z-axis for pitching. */
	nPitching_Ampl_X,           /*!< \brief Number of Pitching amplitudes about the x-axis. */
	nPitching_Ampl_Y,           /*!< \brief Number of Pitching amplitudes about the y-axis. */
	nPitching_Ampl_Z,           /*!< \brief Number of Pitching amplitudes about the z-axis. */
	nPitching_Phase_X,           /*!< \brief Number of Pitching phase offsets about the x-axis. */
	nPitching_Phase_Y,           /*!< \brief Number of Pitching phase offsets about the y-axis. */
	nPitching_Phase_Z,           /*!< \brief Number of Pitching phase offsets about the z-axis. */
	nPlunging_Omega_X,           /*!< \brief Number of Angular frequencies in the x-direction for plunging. */
	nPlunging_Omega_Y,           /*!< \brief Number of Angular frequencies in the y-direction for plunging. */
	nPlunging_Omega_Z,           /*!< \brief Number of Angular frequencies in the z-direction for plunging. */
	nPlunging_Ampl_X,           /*!< \brief Number of Plunging amplitudes in the x-direction. */
	nPlunging_Ampl_Y,           /*!< \brief Number of Plunging amplitudes in the y-direction. */
	nPlunging_Ampl_Z,           /*!< \brief Number of Plunging amplitudes in the z-direction. */
  nMoveMotion_Origin,         /*!< \brief Number of motion origins. */
  *MoveMotion_Origin;         /*!< \brief Keeps track if we should move moment origin. */

  bool ExtraOutput;

	map<string, CAnyOptionRef*> param; /*!< \brief associates option names (strings) with options */

public:
	vector<string> fields; /*!< \brief Tags for the different fields in a restart file. */

	/*! 
	 * \brief Constructor of the class which reads the input file.
	 */
	CConfig(char case_filename[200], unsigned short val_software, unsigned short verb_level);

	/*! 
	 * \brief Destructor of the class. 
	 */
	~CConfig(void);

	/*!
	 * \brief add a scalar option to the param map and set its default value
	 * \param[in] name - name of the option as it appears in the .cfg file
	 * \param[in,out] option - the option to associate with name
	 * \param[in] default_value - option is set to default_value
	 * \tparam T - an arbitary type (int, double, enum, etc)
	 */
	template <class T, class T_default>
	void AddScalarOption(const string & name, T & option, const T_default & default_value) {
		//cout << "Adding Scalar option " << name << endl;
		option = static_cast<T>(default_value);
		CAnyOptionRef* option_ref = new COptionRef<T>(option);
		param.insert( pair<string, CAnyOptionRef*>(string(name), option_ref) );
	}

	/*!
	 * \brief add an enum-based option to the param map and set its default value
	 * \param[in] name - name of the option as it appears in the .cfg file
	 * \param[in,out] option - the option to associate with name
	 * \param[in] Tmap - a map from strings to type Tenum
	 * \tparam T - the option type (usually unsigned short)
	 * \tparam Tenum - an enumeration assocaited with T
	 * \param[in] default_value - option is set to default_value
	 */
	template <class T, class Tenum>
	void AddEnumOption(const string & name, T & option, const map<string, Tenum> & Tmap,
			const string & default_value) {
		//cout << "Adding Enum option " << name << endl;
		typename map<string,Tenum>::const_iterator it;
		it = Tmap.find(default_value);
		if (it == Tmap.end()) {
			cerr << "Error in CConfig::AddEnumOption(string, T&, const map<string, Tenum> &, const string): "
					<< "cannot find " << default_value << " in given map."
					<< endl;
			throw(-1);
		}
		option = it->second;
		CAnyOptionRef* option_ref = new CEnumOptionRef<T,Tenum>(option, Tmap);
		param.insert( pair<string, CAnyOptionRef*>(name, option_ref) );
	}

	/*!
	 * \brief add an enum-based array option to the param map
	 * \param[in] name - name of the option as it appears in the .cfg file
	 * \param[in,out] size - a reference to the size of option
	 * \param[in,out] option - the option to associate with name
	 * \param[in] Tmap - a map from strings to type Tenum
	 * \param[in] update - set to true if the option has already been initialized
	 * \tparam T - the option type (usually unsigned short)
	 * \tparam Tenum - an enumeration assocaited with T
	 */
	template <class T, class Tenum>
	void AddEnumListOption(const string & name, unsigned short & size, T* & option,
			const map<string, Tenum> & Tmap,
			const bool & update = false) {
		//cout << "Adding Enum-List option " << name << endl;
		size = 0;
		if (update && option != NULL) delete [] option;
		CAnyOptionRef* option_ref = new CEnumOptionRef<T,Tenum>(size, option, Tmap);
		param.insert( pair<string, CAnyOptionRef*>(name, option_ref) );
	}

	/*!
	 * \brief add an array option to the param map and set its default value
	 * \param[in] name - name of the option as it appears in the .cfg file
	 * \param[in] size - length of option and default_value arrays
	 * \param[in,out] option - the option to associate with name
	 * \param[in] default_value - option is set to default_value
	 * \param[in] update - set to true if the option has already been initialized
	 * \tparam T - an arbitary type (int, double, enum, etc)
	 *
	 * The option array is allocated in this function.  If memory for
	 * the option array is already allocated, this memory is first released.
	 */
	template <class T>
	void AddArrayOption(const string & name, const int & size, T* & option,
			const T* default_value, const bool & update = false) {
		//cout << "Adding Array option " << name << endl;
		if (update && option != NULL) delete [] option;
		option = new T[size];
		for (int i = 0; i < size; i++)
			option[i] = default_value[i];
		CAnyOptionRef* option_ref = new COptionRef<T>(option, size);
		param.insert( pair<string, CAnyOptionRef*>(name, option_ref) );
	}

	/*!
	 * \brief add a list option to the param map
	 * \param[in] name - name of the option as it appears in the .cfg file
	 * \param[in] size - length of option (will be set by data in .cfg file)
	 * \param[in] option - the option to associate with name
	 * \param[in] update - set to true if the option has already been initialized
	 * \tparam T - an arbitary type (int, double, enum, etc)
	 *
	 * This is similar to AddArrayOption, but is useful for options of
	 * variable size.  Also, this routine does not allow the default
	 * value to be set.
	 */
	template <class T>
	void AddListOption(const string & name, unsigned short & size, T* & option,
			const bool & update = false) {
		//cout << "Adding List option " << name << endl;
		if (update && option != NULL) delete [] option;
		CAnyOptionRef* option_ref = new CListOptionRef<T>(size, option);
		param.insert( pair<string, CAnyOptionRef*>(name, option_ref) );
	}

	/*!
	 * \brief add a special option to the param map and set its default value
	 * \param[in] name - string name of the option as it appears in the .cfg file
	 * \param[in,out] option - the option to associate with name
	 * \param[in] set_value - function to parse string vectors and set option
	 * \param[in] default_value - option is set to default_value
	 * \tparam T - an arbitrary type (int, double, bool, enum, etc)
	 */
	template <class T>
	void AddSpecialOption(const string & name, T & option,
			void (*set_value)(T*, const vector<string>&),
			const T & default_value) {
		//cout << "Adding Special option " << name << endl;
		option = default_value;
		CAnyOptionRef* option_ref = new COptionRef<T>(option, set_value);
		param.insert( pair<string, CAnyOptionRef*>(name, option_ref) );
	}

	/*!
	 * \brief add a marker-type option to the param map
	 * \param[in] name - name of the marker option as it appears in the .cfg file
	 * \param[in,out] num_marker - number of boundary markers
	 * \param[in,out] marker - an array of boundary marker names
	 */
	void AddMarkerOption(const string & name, unsigned short & num_marker, string* & marker);

	/*!
	 * \brief add a convection-discretization type option to the param map
	 * \param[in] name - name of the convection option as it appears in the .cfg file
	 * \param[in] space - the spatial discretization type associataed with name
	 * \param[in] centered - the centered spatial discretization type of name
	 * \param[in] upwind - the upwind spatial discretization type of name
	 */
	void AddConvectOption(const string & name, unsigned short & space, unsigned short & centered,
			unsigned short & upwind);

	/*!
	 * \brief adds the math problem option to the param map
	 * \param[in] name - name of the math problem as it appears in the .cfg file
	 * \param[in] Adjoint - is the continuous adjoint solved?
	 * \param[in] Adjoint_default - the default value for Adjoint
	 * \param[in] OneShot - is a one-shot problem solved?
	 * \param[in] OneShot_default - the default value for OneShot
	 * \param[in] Linearized - is a linearized problem solved?
	 * \param[in] Linearized_default - the default value for Linearized
	 * \param[in] Restart_Flow - is the flow restarted for adjoint and linearized problems?
	 * \param[in] Restart_Flow_default - the default value for Restart_Flow
	 */
	void AddMathProblem(const string & name, bool & Adjoint, const bool & Adjoint_default,
			bool & OneShot, const bool & OneShot_default,
			bool & Linearized, const bool & Linearized_default,
			bool & Restart_Flow, const bool & Restart_Flow_default);

	/*!
	 * \brief adds the design variable parameters option to the param map
	 * \param[in] name - name of the design-variable parameters option in the config file
	 * \param[in] nDV - the number of design variables
	 * \param[in] ParamDV - the parameter values of each design variable
	 * \param[in] Design_Variable - the type of each design variable
	 */
	void AddDVParamOption(const string & name, unsigned short & nDV, double** & ParamDV,
			unsigned short* & Design_Variable);

	/*!
	 * \brief adds a periodic marker option to the param map
	 * \param[in] name - name of the periodic marker option in the config file
	 * \param[in] nMarker_PerBound - the number of periodic marker boundaries
	 * \param[in] Marker_PerBound - string names of periodic boundaries
	 * \param[in] Marker_PerDonor - names of boundaries that supply data to periodic boundaries
	 * \param[in] RotCenter - rotational center for each periodic boundary
	 * \param[in] RotAngles - rotation angles for each periodic boundary
	 * \param[in] Translation - translation vector for each periodic boundary.
	 */
	void AddMarkerPeriodic(const string & name, unsigned short & nMarker_PerBound,
			string* & Marker_PerBound, string* & Marker_PerDonor,
			double** & RotCenter, double** & RotAngles, double** & Translation);

	/*!
	 * \brief adds an inlet marker option to the param map
	 * \param[in] name - name of the inlet marker option in the config file
	 * \param[in] nMarker_Inlet - the number of inlet marker boundaries
	 * \param[in] Marker_Inlet - string names of inlet boundaries
	 * \param[in] Ttotal - specified total temperatures for inlet boundaries
	 * \param[in] Ptotal - specified total pressures for inlet boundaries
	 * \param[in] FlowDir - specified flow direction vector (unit vector) for inlet boundaries
	 */
	void AddMarkerInlet(const string & name, unsigned short & nMarker_Inlet,
			string* & Marker_Inlet, double* & Ttotal, double* & Ptotal,
			double** & FlowDir);

	/*!
	 * \brief adds an inlet marker without flow direction option to the param map
	 * \param[in] name - name of the inlet marker option in the config file
	 * \param[in] nMarker_Inlet - the number of inlet marker boundaries
	 * \param[in] Marker_Inlet - string names of inlet boundaries
	 * \param[in] Ttotal - specified total temperatures for inlet boundaries
	 * \param[in] Ptotal - specified total pressures for inlet boundaries
	 */
	void AddMarkerInlet(const string & name, unsigned short & nMarker_Inlet,
			string* & Marker_Inlet, double* & Ttotal, double* & Ptotal);

	/*!
	 * \brief adds an Dirichlet marker option to the param map
	 * \param[in] name - name of the inlet marker option in the config file
	 * \param[in] nMarker_Dirichlet_Elec - the number of Dirichlet marker boundaries
	 * \param[in] Marker_Dirichlet_Elec - string names of Dirichlet boundaries
	 * \param[in] Dirichlet_Value - specified value of the variable at the boundaries
	 */
	void AddMarkerDirichlet(const string & name, unsigned short & nMarker_Dirichlet_Elec,
			string* & Marker_Dirichlet_Elec, double* & Dirichlet_Value);

	/*!
	 * \brief adds an outlet marker option to the param map
	 * \param[in] name - name of the outlet marker option in the config file
	 * \param[in] nMarker_Outlet - the number of outlet marker boundaries
	 * \param[in] Marker_Outlet - string names of outlet boundaries
	 * \param[in] Pressure - Specified back pressures (static) for outlet boundaries
	 */
	void AddMarkerOutlet(const string & name, unsigned short & nMarker_Outlet,
			string* & Marker_Outlet, double* & Pressure);

	/*!
	 * \brief adds an displacement marker option to the param map
	 * \param[in] name - name of the displacement marker option in the config file
	 * \param[in] nMarker_Outlet - the number of displacement marker boundaries
	 * \param[in] Marker_Outlet - string names of displacement boundaries
	 * \param[in] Displ_Value - Specified displacement for displacement boundaries
	 */
	void AddMarkerDisplacement(const string & name, unsigned short & nMarker_Displacement,
			string* & Marker_Displacement, double* & Displ_Value);

	/*!
	 * \brief adds an load marker option to the param map
	 * \param[in] name - name of the outlet marker option in the config file
	 * \param[in] nMarker_Load - the number of load marker boundaries
	 * \param[in] Marker_Load - string names of load boundaries
	 * \param[in] Load_Value - Specified force for load boundaries
	 */
	void AddMarkerLoad(const string & name, unsigned short & nMarker_Load,
			string* & Marker_Load, double* & Load_Value);

	/*!
	 * \brief adds an load marker option to the param map
	 * \param[in] name - name of the outlet marker option in the config file
	 * \param[in] nMarker_FlowLoad - the number of load marker boundaries
	 * \param[in] Marker_FlowLoad - string names of load boundaries
	 * \param[in] FlowLoad_Value - Specified force for load boundaries
	 */
	void AddMarkerFlowLoad(const string & name, unsigned short & nMarker_FlowLoad,
			string* & Marker_FlowLoad, double* & FlowLoad_Value);

	/*!
	 * \brief used to set Boolean values based on strings "YES" and "NO"
	 * \param[in] ref - a pointer to the boolean value being assigned
	 * \param[in] value - value[0] is "YES" or "NO" and determines the value of ref
	 */
	static void SetBoolOption(bool* ref, const vector<string> & value);

	/*!
	 * \brief breaks an input line from the config file into a set of tokens
	 * \param[in] str - the input line string
	 * \param[out] option_name - the name of the option found at the beginning of the line
	 * \param[out] option_value - the tokens found after the "=" sign on the line
	 * \returns false if the line is empty or a commment, true otherwise
	 */
	bool TokenizeString(string & str, string & option_name,
			vector<string> & option_value);

	/*!
	 * \brief Get information about whether this is a Python config option for design.
	 * \return <code>TRUE</code> if this is a Python config option for design; otherwise <code>FALSE</code>.
	 */
	bool GetPython_Option(string & option_name);

	/*! 
	 * \brief Get reference origin for moment computation.
     * \param[in] val_marker - the marker we are monitoring.
	 * \return Reference origin (in cartesians coordinates) for moment computation.
	 */
	double *GetRefOriginMoment(unsigned short val_marker);

  /*!
	 * \brief Get reference origin x-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \return Reference origin x-coordinate (in cartesians coordinates) for moment computation.
	 */
	double GetRefOriginMoment_X(unsigned short val_marker);
  
  /*!
	 * \brief Get reference origin y-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \return Reference origin y-coordinate (in cartesians coordinates) for moment computation.
	 */
	double GetRefOriginMoment_Y(unsigned short val_marker);
  
  /*!
	 * \brief Get reference origin z-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \return Reference origin z-coordinate (in cartesians coordinates) for moment computation.
	 */
	double GetRefOriginMoment_Z(unsigned short val_marker);
  
  /*!
	 * \brief Set reference origin x-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \param[in] val_origin - New x-coordinate of the mesh motion origin.
	 */
	void SetRefOriginMoment_X(unsigned short val_marker, double val_origin);
  
  /*!
	 * \brief Set reference origin y-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \param[in] val_origin - New y-coordinate of the mesh motion origin.
	 */
	void SetRefOriginMoment_Y(unsigned short val_marker, double val_origin);

  /*!
	 * \brief Set reference origin z-coordinate for moment computation.
   * \param[in] val_marker - the marker we are monitoring.
	 * \param[in] val_origin - New z-coordinate of the mesh motion origin.
	 */
	void SetRefOriginMoment_Z(unsigned short val_marker, double val_origin);

	/*! 
	 * \brief Get maximum number of children in the agglomeration process.
	 * \return Maximum number of children.
	 */
	unsigned short GetMaxChildren(void);

	/*! 
	 * \brief Get the the coordinates where of the box where the grid is going to be deformed.
	 * \return Coordinates where of the box where the grid is going to be deformed.
	 */
	double *GetHold_GridFixed_Coord(void);

	/*! 
	 * \brief Get the power of the dual volume in the grid adaptation sensor.
	 * \return Power of the dual volume in the grid adaptation sensor.
	 */
	double GetDualVol_Power(void);

	/*! 
	 * \brief Get Information about if there is an analytical definition of the surface for doing the 
	 *        grid adaptation.
	 * \return Definition of the surfaces. NONE implies that there isn't any analytical definition 
	 *         and it will use and interpolation.
	 */
	unsigned short GetAnalytical_Surface(void);

	/*! 
	 * \brief Get the maximum dimension of the agglomerated element compared with the whole domain.
	 * \return Maximum dimension of the agglomerated element.
	 */
	double GetMaxDimension(void);

	/*! 
	 * \brief Get the ratio of density for a free surface problem.
	 * \return Ratio of density for a free surface problem.
	 */
	double GetRatioDensity(void);

	/*! 
	 * \brief Get the ratio of viscosity for a free surface problem.
	 * \return Ratio of viscosity for a free surface problem.
	 */
	double GetRatioViscosity(void);

	/*! 
	 * \brief Creates a tecplot file to visualize the partition made by the DDC software.
	 * \return <code>TRUE</code> if the partition is going to be plotted; otherwise <code>FALSE</code>.
	 */
	bool GetVisualize_Partition(void);

  /*!
	 * \brief Creates a tecplot file to visualize the partition made by the DDC software.
	 * \return <code>TRUE</code> if the partition is going to be plotted; otherwise <code>FALSE</code>.
	 */
  bool GetExtraOutput(void);
  
	/*! 
	 * \brief Creates a teot file to visualize the deformation made by the MDC software.
	 * \return <code>TRUE</code> if the deformation is going to be plotted; otherwise <code>FALSE</code>.
	 */
	bool GetVisualize_Deformation(void);

	/*! 
	 * \brief Get the value of the Mach number (velocity divided by speed of sound).
	 * \return Value of the Mach number.
	 */
	double GetMach_FreeStreamND(void);

	/*! 
	 * \brief Get the value of the Gamma of fluid (ratio of specific heats).
	 * \return Value of the constant: Gamma
	 */
	double GetGamma(void);
  
  /*!
	 * \brief Get the value of the limits for the sections.
	 * \return Value of the limits for the sections.
	 */
	double GetSection_Limit(unsigned short val_var);

	/*! 
	 * \brief Get the value of the bulk modulus.
	 * \return Value of the bulk modulus.
	 */
	double GetBulk_Modulus(void);

	/*! 
	 * \brief Get the artificial compresibility factor.
	 * \return Value of the artificial compresibility factor.
	 */
	double GetArtComp_Factor(void);

	/*! 
	 * \brief Get the value of specific gas constant.
	 * \return Value of the constant: Gamma
	 */
	double GetGas_Constant(void);
  
  /*!
	 * \brief Get the value of specific gas constant.
	 * \return Value of the constant: Gamma
	 */
	double GetGas_ConstantND(void);

	/*!
	 * \brief Get the value of wall temperature.
	 * \return Value of the constant: Temperature
	 */
	double GetWallTemperature(void);

	/*!
	 * \brief Get the reference value for the specific gas constant.
	 * \return Reference value for the specific gas constant.
	 */
	double GetGas_Constant_Ref(void);

	/*!
	 * \brief Get the value of the frestream temperature.
	 * \return Freestream temperature.
	 */
	double GetTemperature_FreeStream(void);

	/*!
	 * \brief Get the value of the laminar Prandtl number.
	 * \return Laminar Prandtl number.
	 */
	double GetPrandtl_Lam(void);

	/*!
	 * \brief Get the value of the turbulent Prandtl number.
	 * \return Turbulent Prandtl number.
	 */
	double GetPrandtl_Turb(void);

	/*!
	 * \brief Get the value of the reference length for non-dimensionalization.
	 *        This value should always be 1 internally, and is not user-specified.
	 * \return Reference length for non-dimensionalization.
	 */
	double GetLength_Ref(void);

	/*!
	 * \brief Get the value of the reference pressure for non-dimensionalization.
	 * \return Reference pressure for non-dimensionalization.
	 */
	double GetPressure_Ref(void);

	/*!
	 * \brief Get the value of the reference temperature for non-dimensionalization.
	 * \return Reference temperature for non-dimensionalization.
	 */
	double GetTemperature_Ref(void);

	/*!
	 * \brief Get the value of the reference density for non-dimensionalization.
	 * \return Reference density for non-dimensionalization.
	 */
	double GetDensity_Ref(void);

	/*!
	 * \brief Get the value of the reference velocity for non-dimensionalization.
	 * \return Reference velocity for non-dimensionalization.
	 */
	double GetVelocity_Ref(void);

	/*!
	 * \brief Get the value of the reference time for non-dimensionalization.
	 * \return Reference time for non-dimensionalization.
	 */
	double GetTime_Ref(void);

	/*!
	 * \brief Get the value of the reference viscosity for non-dimensionalization.
	 * \return Reference viscosity for non-dimensionalization.
	 */
	double GetViscosity_Ref(void);

	/*!
	 * \brief Get the value of the reference angular velocity for non-dimensionalization.
	 * \return Reference angular velocity for non-dimensionalization.
	 */
	double GetOmega_Ref(void);

	/*!
	 * \brief Get the value of the reference force for non-dimensionalization.
	 * \return Reference force for non-dimensionalization.
	 */
	double GetForce_Ref(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream pressure.
	 * \return Non-dimensionalized freestream pressure.
	 */
	double GetPressure_FreeStreamND(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream pressure.
	 * \return Non-dimensionalized freestream pressure.
	 */
	double GetPressure_FreeStream(void);

	/*!
	 * \brief Get the vector of the dimensionalized freestream velocity.
	 * \return Dimensionalized freestream velocity vector.
	 */
	double* GetVelocity_FreeStream(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream temperature.
	 * \return Non-dimensionalized freestream temperature.
	 */
	double GetTemperature_FreeStreamND(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream density.
	 * \return Non-dimensionalized freestream density.
	 */
	double GetDensity_FreeStreamND(void);

	/*!
	 * \brief Get the vector of the non-dimensionalized freestream velocity.
	 * \return Non-dimensionalized freestream velocity vector.
	 */
	double* GetVelocity_FreeStreamND(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream energy.
	 * \return Non-dimensionalized freestream energy.
	 */
	double GetEnergy_FreeStreamND(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream viscosity.
	 * \return Non-dimensionalized freestream viscosity.
	 */
	double GetViscosity_FreeStreamND(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream intermittency.
	 * \return Non-dimensionalized freestream intermittency.
	 */
	double GetIntermittency_FreeStream(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream turbulence intensity.
	 * \return Non-dimensionalized freestream intensity.
	 */
	double GetTurbulenceIntensity_FreeStream(void);

	/*!
	 * \brief Get the value of the non-dimensionalized freestream turbulence intensity.
	 * \return Non-dimensionalized freestream intensity.
	 */
	double GetNuFactor_FreeStream(void);

	/*!
	 * \brief Get the value of the turbulent to laminar viscosity ratio.
	 * \return Ratio of turbulent to laminar viscosity ratio.
	 */
	double GetTurb2LamViscRatio_FreeStream(void);
  
	/*!
	 * \brief Get the value of the Reynolds length.
	 * \return Reynolds length.
	 */
	double GetLength_Reynolds(void);

	/*!
	 * \brief Get the conversion factor for converting the grid to meters.
	 * \return Conversion factor for converting the grid to meters.
	 */
	double GetConversion_Factor(void);

	/*! 
	 * \brief Get the start up iterations using the fine grid, this works only for multigrid problems.
	 * \return Start up iterations using the fine grid.
	 */
	unsigned short GetnStartUpIter(void);

	/*! 
	 * \brief Get the reference area for non dimensional coefficient computation. If the value from the 
	 *        is 0 then, the code will compute the reference area using the projection of the shape into
	 *        the z plane (3D) or the x plane (2D).
	 * \return Value of the reference area for coefficient computation.
	 */
	double GetRefAreaCoeff(void);

	/*! 
	 * \brief Get the reference length for computing moment (the default value is 1).
	 * \return Reference length for moment computation.
	 */
	double GetRefLengthMoment(void);

	/*! 
	 * \brief Get the reference element length for computing the slope limiting epsilon.
	 * \return Reference element length for slope limiting epsilon.
	 */
	double GetRefElemLength(void);
  
  /*!
	 * \brief Get the reference coefficient for detecting sharp edges.
	 * \return Reference coefficient for detecting sharp edges.
	 */
	double GetRefSharpEdges(void);

	/*! 
	 * \brief Get the volume of the whole domain using the fine grid, this value is common for all the grids
	 *        in the multigrid method.
	 * \return Volume of the whole domain.
	 */
	double GetDomainVolume(void);

	/*! 
	 * \brief In case the <i>RefAreaCoeff</i> is equal to 0 then, it is necessary to compute a reference area, 
	 *        with this function we set the value of the reference area.
	 * \param[in] val_area - Value of the reference area for non dimensional coefficient computation.
	 */
	void SetRefAreaCoeff(double val_area);

	/*! 
	 * \brief Set the value of the domain volume computed on the finest grid.
	 * \note This volume do not include the volume of the body that is being simulated.
	 * \param[in] val_volume - Value of the domain volume computed on the finest grid.
	 */
	void SetDomainVolume(double val_volume);

	/*! 
	 * \brief Get number of domains in a parallel computation.
	 * \note The number of domains is read from the configuration file or from mpirun -np option.
	 * \return Number of domains in the parallel computation.
	 */
	unsigned short GetnDomain(void);

	/*! 
	 * \brief In case we are running the CFD software, the number of domains is read 
	 *        from <i>MPI::COMM_WORLD.Get_size()</i>.
	 * \param[in] val_ndomain - Number of domains for the MPI parallelization.
	 */
	void SetnDomain(unsigned short val_ndomain);

	/*! 
	 * \brief Set the finest mesh in a multigrid strategy.
	 * \note If we are using a Full Multigrid Strategy or a start up with finest grid, it is necessary 
	 *       to change several times the finest grid.
	 * \param[in] val_finestmesh - Index of the finest grid.
	 */
	void SetFinestMesh(unsigned short val_finestmesh);

	/*! 
	 * \brief Set the kind of time integration scheme.
	 * \note If we are solving different equations it will be necessary to change several 
	 *       times the kind of time integration, to choose the right scheme.
	 * \param[in] val_kind_timeintscheme - Kind of time integration scheme.
	 */		
	void SetKind_TimeIntScheme(unsigned short val_kind_timeintscheme);

	/*! 
	 * \brief Set the parameters of the convective numerical scheme.
	 * \note The parameters will change because we are solving different kind of equations.
	 * \param[in] val_kind_convnumscheme - Center or upwind scheme.
	 * \param[in] val_kind_centered - If centered scheme, kind of centered scheme (JST, etc.).
	 * \param[in] val_kind_upwind - If upwind scheme, kind of upwind scheme (Roe, etc.).
	 * \param[in] val_kind_slopelimit - If upwind scheme, kind of slope limit.
	 */		
	void SetKind_ConvNumScheme(unsigned short val_kind_convnumscheme, unsigned short val_kind_centered, 
			unsigned short val_kind_upwind, unsigned short val_kind_slopelimit);

	/*! 
	 * \brief Set the parameters of the viscous numerical scheme.
	 * \note The parameters will change because we are solving different kind of equations.
	 * \param[in] val_kind_viscnumscheme - Kind of viscous scheme.
	 */
	void SetKind_ViscNumScheme(unsigned short val_kind_viscnumscheme);

	/*! 
	 * \brief Set the parameters of the source term.
	 * \note The parameters will change because we are solving different kind of equations.
	 * \param[in] val_kind_sournumscheme - Kind of source term.
	 */
	void SetKind_SourNumScheme(unsigned short val_kind_sournumscheme);

	/*! 
	 * \brief Get the value of limiter coefficient.
	 * \return Value of the limiter coefficient.
	 */
	double GetLimiterCoeff(void);

  /*!
	 * \brief Get the value of sharp edge limiter.
	 * \return Value of the sharp edge limiter coefficient.
	 */
	double GetSharpEdgesCoeff(void);
  
	/*! 
	 * \brief Get the Reynolds number. Dimensionless number that gives a measure of the ratio of inertial forces 
	 *        to viscous forces and consequently quantifies the relative importance of these two types of forces 
	 *        for given flow condition.
	 * \return Value of the Reynolds number.
	 */
	double GetReynolds(void);

	/*! 
	 * \brief Get the Froude number for free surface problems.
	 * \return Value of the Froude number.
	 */
	double GetFroude(void);

	/*! 
	 * \brief Get the angle of attack of the body. This is the angle between a reference line on a lifting body 
	 *        (often the chord line of an airfoil) and the vector representing the relative motion between the 
	 *        lifting body and the fluid through which it is moving.
	 * \return Value of the angle of attack.
	 */		
	double GetAoA(void);

	/*! 
	 * \brief Get the angle of sideslip of the body. It relates to the rotation of the aircraft centerline from 
	 *        the relative wind.
	 * \return Value of the angle of sideslip.
	 */		
	double GetAoS(void);

	/*! 
	 * \brief Get the charge coefficient that is used in the poissonal potential simulation.
	 * \return Value of the charge coefficient.
	 */		
	double GetChargeCoeff(void);	

	/*! 
	 * \brief Get the number of multigrid levels.
	 * \return Number of multigrid levels (without including the original grid).
	 */
	unsigned short GetMGLevels(void);

	/*!
	 * \brief Set the number of multigrid levels.
	 * \param[in] val_nMultiLevel - Index of the mesh were the CFL is applied
	 */
	void SetMGLevels(unsigned short val_nMultiLevel);

	/*! 
	 * \brief Get the index of the finest grid.
	 * \return Index of the finest grid in a multigrid strategy, this is 0 unless we are 
		       performing a Full multigrid.
	 */		
	unsigned short GetFinestMesh(void);

	/*! 
	 * \brief Get the kind of multigrid (V or W).
	 * \note This variable is used in a recursive way to perform the different kind of cycles
	 * \return 0 or 1 depending of we are dealing with a V or W cycle.
	 */		
	unsigned short GetMGCycle(void);

	/*! 
	 * \brief Get the king of evaluation in the geometrical module.
	 * \return 0 or 1 depending of we are dealing with a V or W cycle.
	 */		
	unsigned short GetGeometryMode(void);

	/*! 
	 * \brief Get the Courant Friedrich Levi number for each grid.
	 * \param[in] val_mesh - Index of the mesh were the CFL is applied.
	 * \return CFL number for each grid.
	 */		
	double GetCFL(unsigned short val_mesh);

	/*!
	 * \brief Get the Courant Friedrich Levi number for each grid, for each species
	 * \param[in] val_mesh - Index of the mesh were the CFL is applied.
	 * \param[in] val_Species - Index of the chemical species
	 * \return CFL number for each grid.
	 */
	double GetCFL(unsigned short val_mesh, unsigned short val_Species);

	/*! 
	 * \brief Get the Courant Friedrich Levi number for unsteady simulations.
	 * \return CFL number for unsteady simulations.
	 */			
	double GetUnst_CFL(void);

	/*! 
	 * \brief Get a parameter of the particular design variable.
	 * \param[in] val_dv - Number of the design variable that we want to read.
	 * \param[in] val_param - Index of the parameter that we want to read.
	 * \return Design variable parameter.
	 */		
	double GetParamDV(unsigned short val_dv, unsigned short val_param);

	/*! 
	 * \brief Get the number of design variables.
	 * \return Number of the design variables.
	 */		
	unsigned short GetnDV(void);

	/*! 
	 * \brief Get the number of Runge-Kutta steps.
	 * \return Number of Runge-Kutta steps.
	 */		
	unsigned short GetnRKStep(void);

	/*! 
	 * \brief Get the total number of boundary markers.
	 * \return Total number of boundary markers.
	 */		
	unsigned short GetnMarker_All(void);
    
    /*!
	 * \brief Get the total number of boundary markers.
	 * \return Total number of boundary markers.
	 */
	unsigned short GetnMarker_NacelleInflow(void);
    
    /*!
	 * \brief Get the total number of boundary markers.
	 * \return Total number of boundary markers.
	 */
	unsigned short GetnMarker_NacelleExhaust(void);
    
    /*!
	 * \brief Get the total number of boundary markers.
	 * \return Total number of boundary markers.
	 */
	unsigned short GetnMarker_NearFieldBound(void);
    
    /*!
	 * \brief Get the total number of boundary markers.
	 * \return Total number of boundary markers.
	 */
	unsigned short GetnMarker_InterfaceBound(void);
    
    /*!
	 * \brief Get the total number of monitoring markers.
	 * \return Total number of monitoring markers.
	 */
	unsigned short GetnMarker_Monitoring(void);
  
  /*!
	 * \brief Get the total number of moving markers.
	 * \return Total number of moving markers.
	 */
	unsigned short GetnMarker_Moving(void);

	/*!
	 * \brief Stores the number of marker in the simulation.
	 * \param[in] val_nmarker - Number of markers of the problem.
	 */	
	void SetnMarker_All(unsigned short val_nmarker);

	/*! 
	 * \brief Get the number of external iterations.
	 * \return Number of external iterations.
	 */
	unsigned long GetnExtIter(void);

	/*! 
	 * \brief Set the number of external iterations.
	 * \note This is important in no time depending methods, where only 
	 *       one external iteration is needed.
	 * \param[in] val_niter - Set the number of external iterations.
	 */
	void SetnExtIter(unsigned long val_niter);

	/*!
	 * \brief Set the current external iteration number.
	 * \param[in] val_iter - Current external iteration number.
	 */
	void SetExtIter(unsigned long val_iter);

	/*!
	 * \brief Set the current internal iteration number.
	 * \param[in] val_iter - Current external iteration number.
	 */
	void SetIntIter(unsigned long val_iter);

	/*!
	 * \brief Get the current internal iteration number.
	 * \return Current external iteration.
	 */
	unsigned long GetExtIter(void);

	/*!
	 * \brief Get the current external iteration number.
	 * \return Current external iteration.
	 */
	unsigned long GetIntIter(void);

	/*! 
	 * \brief Get the frequency for writing the solution file.
	 * \return It writes the solution file with this frequency.
	 */		
	unsigned long GetWrt_Sol_Freq(void);

	/*!
	 * \brief Get the frequency for writing the convergence file.
	 * \return It writes the convergence file with this frequency.
	 */		
	unsigned long GetWrt_Con_Freq(void);

	/*!
	 * \brief Get information about writing a volume solution file.
	 * \return <code>TRUE</code> means that a volume solution file will be written.
	 */
	bool GetWrt_Vol_Sol(void);

	/*!
	 * \brief Get information about writing a surface solution file.
	 * \return <code>TRUE</code> means that a surface solution file will be written.
	 */
	bool GetWrt_Srf_Sol(void);

	/*!
	 * \brief Get information about writing a surface comma-separated values (CSV) solution file.
	 * \return <code>TRUE</code> means that a surface comma-separated values (CSV) solution file will be written.
	 */
	bool GetWrt_Csv_Sol(void);

	/*!
	 * \brief Get information about writing a restart solution file.
	 * \return <code>TRUE</code> means that a restart solution file will be written.
	 */
	bool GetWrt_Restart(void);

	/*!
	 * \brief Get information about writing residuals to volume solution file.
	 * \return <code>TRUE</code> means that residuals will be written to the solution file.
	 */
	bool GetWrt_Residuals(void);

  /*!
	 * \brief Get information about writing rind layers to the solution files.
	 * \return <code>TRUE</code> means that rind layers will be written to the solution file.
	 */
	bool GetWrt_Halo(void);

  /*!
	 * \brief Get information about writing sectional force files.
	 * \return <code>TRUE</code> means that sectional force files will be written for specified markers.
	 */
	bool GetWrt_Sectional_Forces(void);
  
	/*!
	 * \brief Get the alpha (convective) coefficients for the Runge-Kutta integration scheme.
	 * \param[in] val_step - Index of the step.
	 * \return Alpha coefficient for the Runge-Kutta integration scheme.
	 */		
	double Get_Alpha_RKStep(unsigned short val_step);

	/*! 
	 * \brief Get the index of the surface defined in the geometry file.
	 * \param[in] val_marker - Value of the marker in which we are interested.
	 * \return Value of the index that is in the geometry file for the surface that 
	 *         has the marker <i>val_marker</i>.
	 */		
	string GetMarker_All_Tag(unsigned short val_marker);
    
    /*!
	 * \brief Get the name of the surface defined in the geometry file.
	 * \param[in] val_marker - Value of the marker in which we are interested.
	 * \return Name that is in the geometry file for the surface that
	 *         has the marker <i>val_marker</i>.
	 */
	string GetMarker_Monitoring(unsigned short val_marker);
    
	/*! 
	 * \brief Get the tag if the iMarker defined in the geometry file.
	 * \param[in] val_tag - Value of the tag in which we are interested.
	 * \return Value of the marker <i>val_marker</i> that is in the geometry file 
	 *         for the surface that has the tag.
	 */		
	unsigned short GetTag_Marker_All(string val_tag);

	/*! 
	 * \brief Get the kind of boundary for each marker.
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \return Kind of boundary for the marker <i>val_marker</i>.
	 */		
	unsigned short GetMarker_All_Boundary(unsigned short val_marker);

	/*! 
	 * \brief Set the value of the boundary <i>val_boundary</i> (read from the config file) 
	 *        for the marker <i>val_marker</i>.
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_boundary - Kind of boundary read from config file.
	 */		
	void SetMarker_All_Boundary(unsigned short val_marker, unsigned short val_boundary);

	/*! 
	 * \brief Set the value of the index <i>val_index</i> (read from the geometry file) for 
	 *        the marker <i>val_marker</i>.
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_index - Index of the surface read from geometry file.
	 */	
	void SetMarker_All_Tag(unsigned short val_marker, string val_index);

	/*! 
	 * \brief Set if a marker <i>val_marker</i> is going to be monitored <i>val_monitoring</i> 
	 *        (read from the config file).
	 * \note This is important for non dimensional coefficient computation.
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_monitoring - 0 or 1 depending if the the marker is going to be monitored.
	 */	
	void SetMarker_All_Monitoring(unsigned short val_marker, unsigned short val_monitoring);
  
  /*!
	 * \brief Set if a marker <i>val_marker</i> is going to be designed <i>val_designing</i>
	 *        (read from the config file).
	 * \note This is important for non dimensional coefficient computation.
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_monitoring - 0 or 1 depending if the the marker is going to be designed.
	 */
	void SetMarker_All_Designing(unsigned short val_marker, unsigned short val_designing);

	/*! 
	 * \brief Set if a marker <i>val_marker</i> is going to be plot <i>val_plotting</i> 
	 *        (read from the config file).
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_plotting - 0 or 1 depending if the the marker is going to be plot.
	 */	
	void SetMarker_All_Plotting(unsigned short val_marker, unsigned short val_plotting);

	/*! 
	 * \brief Set if a marker <i>val_marker</i> is going to be affected by design variables <i>val_moving</i> 
	 *        (read from the config file).
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_DV - 0 or 1 depending if the the marker is affected by design variables.
	 */	
	void SetMarker_All_DV(unsigned short val_marker, unsigned short val_DV);
  
  /*!
	 * \brief Set if a marker <i>val_marker</i> is going to be moved <i>val_moving</i>
	 *        (read from the config file).
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_moving - 0 or 1 depending if the the marker is going to be moved.
	 */
	void SetMarker_All_Moving(unsigned short val_marker, unsigned short val_moving);

	/*! 
	 * \brief Set if a marker <i>val_marker</i> is going to be periodic <i>val_perbound</i> 
	 *        (read from the config file).
	 * \param[in] val_marker - Index of the marker in which we are interested.
	 * \param[in] val_perbound - Index of the surface with the periodic boundary.
	 */	
	void SetMarker_All_PerBound(unsigned short val_marker, short val_perbound);

	/*! 
	 * \brief Set if a marker <i>val_marker</i> is going to be sent or receive <i>val_index</i> 
	 *        from another domain.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be moved.
	 * \param[in] val_index - Index of the surface read from geometry file.
	 */		
	void SetMarker_All_SendRecv(unsigned short val_marker, short val_index);

	/*! 
	 * \brief Get the send-receive information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be moved.
	 * \return If positive, the information is sended to that domain, in case negative 
	 *         the information is receive from that domain.
	 */		
	short GetMarker_All_SendRecv(unsigned short val_marker);

	/*! 
	 * \brief Get an internal index that identify the periodic boundary conditions.
	 * \param[in] val_marker - Value of the marker that correspond with the periodic boundary.
	 * \return The internal index of the periodic boundary condition. 
	 */		
	short GetMarker_All_PerBound(unsigned short val_marker);

	/*! 
	 * \brief Get the monitoring information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be monitored.
	 * \return 0 or 1 depending if the marker is going to be monitored.
	 */		
	unsigned short GetMarker_All_Monitoring(unsigned short val_marker);
  
  /*!
	 * \brief Get the design information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be monitored.
	 * \return 0 or 1 depending if the marker is going to be monitored.
	 */
	unsigned short GetMarker_All_Designing(unsigned short val_marker);

	/*! 
	 * \brief Get the plotting information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be moved.
	 * \return 0 or 1 depending if the marker is going to be plotted.
	 */		
	unsigned short GetMarker_All_Plotting(unsigned short val_marker);

	/*! 
	 * \brief Get the DV information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be affected by design variables.
	 * \return 0 or 1 depending if the marker is going to be affected by design variables.
	 */		
	unsigned short GetMarker_All_DV(unsigned short val_marker);

  /*!
	 * \brief Get the motion information for a marker <i>val_marker</i>.
	 * \param[in] val_marker - 0 or 1 depending if the the marker is going to be moved.
	 * \return 0 or 1 depending if the marker is going to be moved.
	 */
	unsigned short GetMarker_All_Moving(unsigned short val_marker);
  
	/*! 
	 * \brief Get the number of pre-smoothings in a multigrid strategy.
	 * \param[in] val_mesh - Index of the grid.
	 * \return Number of smoothing iterations.
	 */
	unsigned short GetMG_PreSmooth(unsigned short val_mesh);

	/*! 
	 * \brief Get the number of post-smoothings in a multigrid strategy.
	 * \param[in] val_mesh - Index of the grid.
	 * \return Number of smoothing iterations.
	 */		
	unsigned short GetMG_PostSmooth(unsigned short val_mesh);

	/*! 
	 * \brief Get the number of implicit Jacobi smoothings of the correction in a multigrid strategy.
	 * \param[in] val_mesh - Index of the grid.
	 * \return Number of implicit smoothing iterations.
	 */		
	unsigned short GetMG_CorrecSmooth(unsigned short val_mesh);

	/*! 
	 * \brief Governing equations of the flow (it can be different from the run time equation).
	 * \param[in] val_zone - Zone where the soler is applied.
	 * \return Governing equation that we are solving.
	 */		
	unsigned short GetKind_Solver(void);

  /*!
	 * \brief Governing equations of the flow (it can be different from the run time equation).
	 * \param[in] val_zone - Zone where the soler is applied.
	 * \return Governing equation that we are solving.
	 */
	unsigned short GetKind_Regime(void);

	/*! 
	 * \brief Get the kind of method for computation of spatial gradients.
	 * \return Numerical method for computation of spatial gradients.
	 */		
	unsigned short GetKind_Gradient_Method(void);

	/*!
	 * \brief Get the kind of solver for the implicit solver.
	 * \return Numerical solver for implicit formulation (solving the linear system).
	 */
	unsigned short GetKind_Linear_Solver(void);

	/*!
	 * \brief Get the kind of preconditioner for the implicit solver.
	 * \return Numerical preconditioner for implicit formulation (solving the linear system).
	 */
	unsigned short GetKind_Linear_Solver_Prec(void);

	/*!
	 * \brief Set the kind of preconditioner for the implicit solver.
	 * \return Numerical preconditioner for implicit formulation (solving the linear system).
	 */
	void SetKind_Linear_Solver_Prec(unsigned short val_kind_prec);

	/*!
	 * \brief Get min error of the linear solver for the implicit formulation.
	 * \return Min error of the linear solver for the implicit formulation.
	 */
	double GetLinear_Solver_Error(void);

	/*! 
	 * \brief Get max number of iterations of the linear solver for the implicit formulation.
	 * \return Max number of iterations of the linear solver for the implicit formulation.
	 */
	unsigned long GetLinear_Solver_Iter(void);

	/*!
	 * \brief Get the relaxation coefficient of the linear solver for the implicit formulation.
	 * \return relaxation coefficient of the linear solver for the implicit formulation.
	 */
	double GetLinear_Solver_Relax(void);
  
  /*!
	 * \brief Get the number of increments for mesh deformation.
	 * \return Number of increments for mesh deformation.
	 */
	unsigned long GetGridDef_Iter(void);

	/*!
	 * \brief Get the kind of SU2 software component.
	 * \return Kind of the SU2 software component.
	 */
	unsigned short GetKind_SU2(void);

	/*! 
	 * \brief Get the kind of the turbulence model.
	 * \return Kind of the turbulence model.
	 */
	unsigned short GetKind_Turb_Model(void);

	/*! 
	 * \brief Get the kind of time integration method.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.
	 * \return Kind of time integration method.
	 */
	unsigned short GetKind_TimeIntScheme(void);

	/*! 
	 * \brief Get the kind of convective numerical scheme.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.	 
	 * \return Kind of the convective scheme.
	 */		
	unsigned short GetKind_ConvNumScheme(void);

	/*! 
	 * \brief Get the kind of viscous numerical scheme.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.	 
	 * \return Kind of the viscous scheme.
	 */		
	unsigned short GetKind_ViscNumScheme(void);

	/*! 
	 * \brief Get the kind scheme for the source term integration.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.	 
	 * \return Scheme for the source term integration.
	 */		
	unsigned short GetKind_SourNumScheme(void);

	/*! 
	 * \brief Get kind of center scheme for the convective terms.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.	 
	 * \return Kind of center scheme for the convective terms.
	 */		
	unsigned short GetKind_Centered(void);

	/*! 
	 * \brief Get kind of upwind scheme for the convective terms.
	 * \note This is the information that the code will use, the method will 
	 *       change in runtime depending of the specific equation (direct, adjoint, 
	 *       linearized) that is being solved.	 
	 * \return Kind of upwind scheme for the convective terms.
	 */		
	unsigned short GetKind_Upwind(void);

	/*! 
	 * \brief Get the kind of integration scheme (explicit or implicit) 
	 *        for the flow equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of integration scheme for the flow equations.
	 */
	unsigned short GetKind_TimeIntScheme_Flow(void);

	/*! 
	 * \brief Get the kind of integration scheme (explicit or implicit) 
	 *        for the template equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of integration scheme for the plasma equations.
	 */
	unsigned short GetKind_TimeIntScheme_Template(void);

	/*! 
	 * \brief Get the kind of convective numerical scheme for the flow 
	 *        equations (centered or upwind).
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of convective numerical scheme for the flow equations.
	 */		
	unsigned short GetKind_ConvNumScheme_Flow(void);

	/*! 
	 * \brief Get the kind of convective numerical scheme for the template 
	 *        equations (centered or upwind).
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of convective numerical scheme for the flow equations.
	 */		
	unsigned short GetKind_ConvNumScheme_Template(void);

	/*! 
	 * \brief Get the kind of viscous numerical scheme for the flow
	 *        equations (Galerkin, Average of gradients, Average of gradients
	 *        with correction).
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of viscous numerical scheme for the flow equations.
	 */		
	unsigned short GetKind_ViscNumScheme_Flow(void);

	/*! 
	 * \brief Get the kind of viscous numerical scheme for the plasma
	 *        equations (Galerkin, Average of gradients)
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of viscous numerical scheme for the flow equations.
	 */		
	unsigned short GetKind_ViscNumScheme_Template(void);

	/*! 
	 * \brief Get the kind of source term for the flow equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of source term for the flow equations.
	 */			
	unsigned short GetKind_SourNumScheme_Flow(void);

	/*! 
	 * \brief Get the kind of source term for the plasma equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of source term for the flow equations.
	 */			
	unsigned short GetKind_SourNumScheme_Template(void);

	/*! 
	 * \brief Get the kind of center convective numerical scheme for the flow equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of center convective numerical scheme for the flow equations.
	 */
	unsigned short GetKind_Centered_Flow(void);

	/*! 
	 * \brief Get the kind of center convective numerical scheme for the plasma equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of center convective numerical scheme for the flow equations.
	 */
	unsigned short GetKind_Centered_Template(void);

	/*! 
	 * \brief Get the kind of upwind convective numerical scheme for the flow equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of upwind convective numerical scheme for the flow equations.
	 */
	unsigned short GetKind_Upwind_Flow(void);

	/*! 
	 * \brief Get the method for limiting the spatial gradients.
	 * \return Method for limiting the spatial gradients.
	 */		
	unsigned short GetKind_SlopeLimit(void);

	/*! 
	 * \brief Get the method for limiting the spatial gradients.
	 * \return Method for limiting the spatial gradients solving the flow equations.
	 */		
	unsigned short GetKind_SlopeLimit_Flow(void);

	/*! 
	 * \brief Get the method for limiting the spatial gradients.
	 * \return Method for limiting the spatial gradients solving the turbulent equation.
	 */		
	unsigned short GetKind_SlopeLimit_Turb(void);

	/*!
	 * \brief Value of the calibrated constant for the Lax method (center scheme).
	 * \note This constant is used in coarse levels and with first order methods.
	 * \return Calibrated constant for the Lax method.
	 */		
	double GetKappa_1st_Flow(void);

	/*! 
	 * \brief Value of the calibrated constant for the JST method (center scheme).
	 * \return Calibrated constant for the JST method for the flow equations.
	 */		
	double GetKappa_2nd_Flow(void);

	/*! 
	 * \brief Value of the calibrated constant for the JST method (center scheme).
	 * \return Calibrated constant for the JST method for the flow equations.
	 */		
	double GetKappa_4th_Flow(void);

	/*! 
	 * \brief Get the kind of integration scheme (implicit) 
	 *        for the turbulence equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of integration scheme for the turbulence equations.
	 */
	unsigned short GetKind_TimeIntScheme_Turb(void);

	/*! 
	 * \brief Get the kind of convective numerical scheme for the turbulence 
	 *        equations (upwind).
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of convective numerical scheme for the turbulence equations.
	 */
	unsigned short GetKind_ConvNumScheme_Turb(void);

	/*! 
	 * \brief Get the kind of viscous numerical scheme for the turbulence
	 *        equations (Galerkin, Average of gradients, Average of gradients
	 *        with correction).
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of viscous numerical scheme for the turbulence equations.
	 */	
	unsigned short GetKind_ViscNumScheme_Turb(void);

	/*! 
	 * \brief Get the kind of source term for the turbulence equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of source term for the turbulence equations.
	 */
	unsigned short GetKind_SourNumScheme_Turb(void);

	/*! 
	 * \brief Get the kind of center convective numerical scheme for the turbulence equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of center convective numerical scheme for the turbulence equations.
	 */
	unsigned short GetKind_Centered_Turb(void);

	/*! 
	 * \brief Get the kind of upwind convective numerical scheme for the turbulence equations.
	 * \note This value is obtained from the config file, and it is constant 
	 *       during the computation.
	 * \return Kind of upwind convective numerical scheme for the turbulence equations.
	 */	
	unsigned short GetKind_Upwind_Turb(void);

	/*!
	 * \brief Get the kind of inlet boundary condition treatment (total conditions or mass flow).
	 * \return Kind of inlet boundary condition.
	 */
	unsigned short GetKind_Inlet(void);

	/*! 
	 * \brief Provides information about the the nodes that are going to be moved on a deformation 
	 *        volumetric grid deformation.
	 * \return <code>TRUE</code> means that only the points on the FFD box will be moved.
	 */
	bool GetHold_GridFixed(void);

	/*! 
	 * \brief Provides information about the time integration, and change the write in the output 
	 *        files information about the iteration.
	 * \return The kind of time integration: Steady state, time stepping method (unsteady) or 
	 *         dual time stepping method (unsteady).
	 */
	unsigned short GetUnsteady_Simulation(void);

	/*!
	 * \brief Provides the restart information.
	 * \return Restart information, if <code>TRUE</code> then the code will use the solution as restart.
	 */		
	bool GetRestart(void);

	/*!
	 * \brief Provides the number of varaibles.
	 * \return Number of variables.
	 */
	unsigned short GetnVar(void);
  
  /*!
	 * \brief Provides the number of varaibles.
	 * \return Number of variables.
	 */
	unsigned short GetnZone(void);
  
  /*!
	 * \brief Provides the number of varaibles.
	 * \return Number of variables.
	 */
	unsigned short GetiZone(void);

	/*! 
	 * \brief For some problems like adjoint or the linearized equations it 
	 *		  is necessary to restart the flow solution.
	 * \return Flow restart information, if <code>TRUE</code> then the code will restart the flow solution.
	 */

	bool GetRestart_Flow(void);
  
  /*!
   * \brief Indicates whether electron gas is present in the gas mixture.
   */
  bool GetIonization(void);

	/*! 
	 * \brief Information about doing a full multigrid strategy (start in the coarse level).
	 * \return <code>TRUE</code> or <code>FALSE</code>  depending if we are performing a full multigrid strategy.
	 */		
	bool GetFullMG(void);

	/*! 
	 * \brief Information about computing and plotting the equivalent area distribution.
	 * \return <code>TRUE</code> or <code>FALSE</code>  depending if we are computing the equivalent area.
	 */		
	bool GetEquivArea(void);

	/*! 
	 * \brief Get name of the input grid.
	 * \return File name of the input grid.
	 */
	string GetMesh_FileName(void);

	/*! 
	 * \brief Get name of the output grid, this parameter is important for grid 
	 *        adaptation and deformation.
	 * \return File name of the output grid.
	 */
	string GetMesh_Out_FileName(void);

	/*! 
	 * \brief Get the name of the file with the solution of the flow problem.
	 * \return Name of the file with the solution of the flow problem.
	 */
	string GetSolution_FlowFileName(void);

	/*!
	 * \brief Get the name of the file with the solution of the linearized flow problem.
	 * \return Name of the file with the solution of the linearized flow problem.
	 */
	string GetSolution_LinFileName(void);

	/*! 
	 * \brief Get the name of the file with the solution of the adjoint flow problem 
	 *		  with drag objective function.
	 * \return Name of the file with the solution of the adjoint flow problem with 
	 *         drag objective function.
	 */
	string GetSolution_AdjFileName(void);

	/*! 
	 * \brief Get the name of the file with the residual of the problem.
	 * \return Name of the file with the residual of the problem.
	 */
	string GetResidual_FileName(void);

	/*! 
	 * \brief Get the format of the input/output grid.
	 * \return Format of the input/output grid.
	 */
	unsigned short GetMesh_FileFormat(void);

	/*! 
	 * \brief Get the format of the output solution.
	 * \return Format of the output solution.
	 */
	unsigned short GetOutput_FileFormat(void);

	/*! 
	 * \brief Get the name of the file with the convergence history of the problem.
	 * \return Name of the file with convergence history of the problem.
	 */
	string GetConv_FileName(void);

	/*! 
	 * \brief Get the name of the file with the flow variables.
	 * \return Name of the file with the primitive variables.
	 */		
	string GetFlow_FileName(void);

	/*! 
	 * \brief Get the name of the file with the structure variables.
	 * \return Name of the file with the structure variables.
	 */		
	string GetStructure_FileName(void);
  
  /*!
	 * \brief Get the name of the file with the structure variables.
	 * \return Name of the file with the structure variables.
	 */
	string GetSurfStructure_FileName(void);
  
  /*!
	 * \brief Get the name of the file with the structure variables.
	 * \return Name of the file with the structure variables.
	 */
	string GetSurfWave_FileName(void);
  
  /*!
	 * \brief Get the name of the file with the structure variables.
	 * \return Name of the file with the structure variables.
	 */
	string GetSurfHeat_FileName(void);

	/*!
	 * \brief Get the name of the file with the wave variables.
	 * \return Name of the file with the wave variables.
	 */		
	string GetWave_FileName(void);
  
  /*!
	 * \brief Get the name of the file with the wave variables.
	 * \return Name of the file with the wave variables.
	 */
	string GetHeat_FileName(void);

	/*!
	 * \brief Get the name of the file with the adjoint wave variables.
	 * \return Name of the file with the adjoint wave variables.
	 */		
	string GetAdjWave_FileName(void);

	/*! 
	 * \brief Get the name of the restart file for the wave variables.
	 * \return Name of the restart file for the flow variables.
	 */
	string GetRestart_WaveFileName(void);

	/*! 
	 * \brief Get the name of the restart file for the heat variables.
	 * \return Name of the restart file for the flow variables.
	 */
	string GetRestart_HeatFileName(void);

	/*! 
	 * \brief Get the name of the restart file for the flow variables.
	 * \return Name of the restart file for the flow variables.
	 */
	string GetRestart_FlowFileName(void);

	/*! 
	 * \brief Get the name of the restart file for the linearized flow variables.
	 * \return Name of the restart file for the linearized flow variables.
	 */
	string GetRestart_LinFileName(void);

	/*! 
	 * \brief Get the name of the restart file for the adjoint variables (drag objective function).
	 * \return Name of the restart file for the adjoint variables (drag objective function).
	 */
	string GetRestart_AdjFileName(void);

	/*! 
	 * \brief Get the name of the file with the adjoint variables.
	 * \return Name of the file with the adjoint variables.
	 */
	string GetAdj_FileName(void);

	/*! 
	 * \brief Get the name of the file with the linearized flow variables.
	 * \return Name of the file with the linearized flow variables.
	 */
	string GetLin_FileName(void);	

	/*! 
	 * \brief Get the name of the file with the gradient of the objective function.
	 * \return Name of the file with the gradient of the objective function.
	 */
	string GetObjFunc_Grad_FileName(void);

	/*! 
	 * \brief Get the name of the file with the gradient of the objective function.
	 * \return Name of the file with the gradient of the objective function.
	 */
	string GetObjFunc_Value_FileName(void);

	/*! 
	 * \brief Get the name of the file with the surface information for the flow problem.
	 * \return Name of the file with the surface information for the flow problem.
	 */
	string GetSurfFlowCoeff_FileName(void);

	/*! 
	 * \brief Get the name of the file with the surface information for the adjoint problem.
	 * \return Name of the file with the surface information for the adjoint problem.
	 */
	string GetSurfAdjCoeff_FileName(void);

	/*! 
	 * \brief Get the name of the file with the surface information for the linearized flow problem.
	 * \return Name of the file with the surface information for the linearized flow problem.
	 */
	string GetSurfLinCoeff_FileName(void);
  
  /*!
	 * \brief Augment the input filename with the iteration number for an unsteady file.
   * \param[in] val_filename - String value of the base filename.
   * \param[in] val_iter - Unsteady iteration number or time spectral instance.
	 * \return Name of the file with the iteration numer for an unsteady solution file.
	 */
  string GetUnsteady_FileName(string val_filename, int val_iter);

  /*!
	 * \brief Append the input filename string with the appropriate objective function extension.
   * \param[in] val_filename - String value of the base filename.
	 * \return Name of the file with the appropriate objective function extension.
	 */
  string GetObjFunc_Extension(string val_filename);
  
	/*! 
	 * \brief Get functional that is going to be used to evaluate the flow convergence.
	 * \return Functional that is going to be used to evaluate the flow convergence.
	 */
	unsigned short GetCauchy_Func_Flow(void);

	/*! 
	 * \brief Get functional that is going to be used to evaluate the adjoint flow convergence.
	 * \return Functional that is going to be used to evaluate the adjoint flow convergence.
	 */
	unsigned short GetCauchy_Func_AdjFlow(void);

	/*! 
	 * \brief Get functional that is going to be used to evaluate the linearized flow convergence.
	 * \return Functional that is going to be used to evaluate the linearized flow convergence.
	 */
	unsigned short GetCauchy_Func_LinFlow(void);

	/*! 
	 * \brief Get the number of iterations that are considered in the Cauchy convergence criteria.
	 * \return Number of elements in the Cauchy criteria.
	 */
	unsigned short GetCauchy_Elems(void);

	/*! 
	 * \brief Get the number of iterations that are not considered in the convergence criteria.
	 * \return Number of iterations before starting with the convergence criteria.
	 */
	unsigned long GetStartConv_Iter(void);

	/*! 
	 * \brief Get the value of convergence criteria for the Cauchy method in the direct, 
	 *        adjoint or linearized problem.
	 * \return Value of the convergence criteria.
	 */
	double GetCauchy_Eps(void);

	/*! 
	 * \brief Get the value of convergence criteria for the one-shot problem.
	 * \return Value of the convergence criteria.
	 */
	double GetCauchy_Eps_OneShot(void);

	/*! 
	 * \brief Get the value of convergence criteria for the full multigrid method.
	 * \return Value of the convergence criteria.
	 */
	double GetCauchy_Eps_FullMG(void);

	/*! 
	 * \brief Divide the rectbles and hexahedron.
	 * \return <code>TRUE</code> if the elements must be divided; otherwise <code>FALSE</code>.
	 */
	bool GetDivide_Element(void);

	/*! 
	 * \brief Value of the design variable step, we use this value in design problems.
	 * \param[in] val_dv - Number of the design variable that we want to read.
	 * \return Design variable step.
	 */	
	double GetDV_Value(unsigned short val_dv);
  
	/*!
	 * \brief Get the minimum value of Beta for Roe-Turkel preconditioner
	 * \return the minimum value of Beta for Roe-Turkel preconditioner
	 */
	double GetminTurkelBeta();

	/*!
	 * \brief Get the minimum value of Beta for Roe-Turkel preconditioner
	 * \return the minimum value of Beta for Roe-Turkel preconditioner
	 */
	double GetmaxTurkelBeta();

	/*!
	 * \brief Get information about the adibatic wall condition
	 * \return <code>TRUE</code> if it is a adiabatic wall condition; otherwise <code>FALSE</code>.
	 */
	bool GetAdiabaticWall(void);

	/*!
	 * \brief Get information about the isothermal wall condition
	 * \return <code>TRUE</code> if it is a isothermal wall condition; otherwise <code>FALSE</code>.
	 */
	bool GetIsothermalWall(void);

	/*!
	 * \brief Get information about the catalytic wall condition
	 * \return <code>TRUE</code> if it is a catalytic wall condition; otherwise <code>FALSE</code>.
	 */
	bool GetCatalyticWall(void);

	/*!
	 * \brief Get information about the Low Mach Preconditioning
	 * \return <code>TRUE</code> if we are using low Mach preconditioner; otherwise <code>FALSE</code>.
	 */
	bool Low_Mach_Preconditioning(void);

	/*!
	 * \brief Get information about the poisson solver condition
	 * \return <code>TRUE</code> if it is a poisson solver condition; otherwise <code>FALSE</code>.
	 */
	bool GetPoissonSolver(void);

	/*! 
	 * \brief Get information about the gravity force.
	 * \return <code>TRUE</code> if it uses the gravity force; otherwise <code>FALSE</code>.
	 */
	bool GetGravityForce(void);

	/*!
	 * \brief Get information about the rotational frame.
	 * \return <code>TRUE</code> if there is a rotational frame; otherwise <code>FALSE</code>.
	 */
	bool GetRotating_Frame(void);

	/*! 
	 * \brief Get information about the axisymmetric frame.
	 * \return <code>TRUE</code> if there is a rotational frame; otherwise <code>FALSE</code>.
	 */
	bool GetAxisymmetric(void);

	/*! 
	 * \brief Get information about there is a smoothing of the grid coordinates.
	 * \return <code>TRUE</code> if there is smoothing of the grid coordinates; otherwise <code>FALSE</code>.
	 */	
	bool GetAdaptBoundary(void);

	/*! 
	 * \brief Get information about there is a smoothing of the grid coordinates.
	 * \return <code>TRUE</code> if there is smoothing of the grid coordinates; otherwise <code>FALSE</code>.
	 */	
	bool GetSmoothNumGrid(void);

	/*! 
	 * \brief Set information about there is a smoothing of the grid coordinates.
	 * \param[in] val_smoothnumgrid - <code>TRUE</code> if there is smoothing of the grid coordinates; otherwise <code>FALSE</code>.
	 */
	void SetSmoothNumGrid(bool val_smoothnumgrid);

	/*! 
	 * \brief Subtract one to the index of the finest grid (full multigrid strategy).
	 * \return Change the index of the finest grid.
	 */
	void SubtractFinestMesh(void);

	/*! 
	 * \brief Obtain the kind of design variable.
	 * \param[in] val_dv - Number of the design variable that we want to read.
	 * \return Design variable identification.
	 */
	unsigned short GetDesign_Variable(unsigned short val_dv);

	/*! 
	 * \brief Obtain the kind of convergence criteria to establish the convergence of the CFD code.
	 * \return Kind of convergence criteria.
	 */
	unsigned short GetConvCriteria(void);

	/*! 
	 * \brief This subroutine adds the domain index to the name of some input-output file names.
	 * \param[in] val_domain - Index of the domain.
	 */
	void SetFileNameDomain(unsigned short val_domain);

	/*! 
	 * \brief Get the index in the config information of the marker <i>val_marker</i>.
	 * \note When we read the config file, it stores the markers in a particular vector.
	 * \return Index in the config information of the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_Tag(string val_marker);

	/*! 
	 * \brief Get the boundary information (kind of boundary) in the config information of the marker <i>val_marker</i>.
	 * \return Kind of boundary in the config information of the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_Boundary(string val_marker);

	/*! 
	 * \brief Get the monitoring information from the config definition for the marker <i>val_marker</i>.
	 * \return Monitoring information of the boundary in the config information for the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_Monitoring(string val_marker);
  
  /*!
	 * \brief Get the monitoring information from the config definition for the marker <i>val_marker</i>.
	 * \return Monitoring information of the boundary in the config information for the marker <i>val_marker</i>.
	 */
	unsigned short GetMarker_Config_Designing(string val_marker);

	/*! 
	 * \brief Get the plotting information from the config definition for the marker <i>val_marker</i>.
	 * \return Plotting information of the boundary in the config information for the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_Plotting(string val_marker);

	/*! 
	 * \brief Get the DV information from the config definition for the marker <i>val_marker</i>.
	 * \return DV information of the boundary in the config information for the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_DV(string val_marker);

  /*!
	 * \brief Get the motion information from the config definition for the marker <i>val_marker</i>.
	 * \return Motion information of the boundary in the config information for the marker <i>val_marker</i>.
	 */
	unsigned short GetMarker_Config_Moving(string val_marker);
  
	/*! 
	 * \brief Get the periodic information from the config definition of the marker <i>val_marker</i>.
	 * \return Periodic information of the boundary in the config information of the marker <i>val_marker</i>.
	 */	
	unsigned short GetMarker_Config_PerBound(string val_marker);

	/*! 
	 * \brief Determines if problem is adjoint
	 * \return true if Adjoint
	 */
	bool GetAdjoint(void);
    
    /*!
	 * \brief Determines if problem is viscous
	 * \return true if Viscous
	 */
	bool GetViscous(void);

	/*!
	 * \brief Provides the index of the solution in the container.
	 * \param[in] val_eqsystem - Equation that is being solved.
	 * \return Index on the solution container.
	 */	
	unsigned short GetContainerPosition(unsigned short val_eqsystem);

	/*! 
	 * \brief Value of the order of magnitude reduction of the residual.
	 * \return Value of the order of magnitude reduction of the residual.
	 */	
	double GetOrderMagResidual(void);

	/*! 
	 * \brief Value of the minimum residual value (log10 scale).
	 * \return Value of the minimum residual value (log10 scale).
	 */	
	double GetMinLogResidual(void);
    
	/*! 
	 * \brief Value of the damping factor for the residual restriction.
	 * \return Value of the damping factor.
	 */	
	double GetDamp_Res_Restric(void);

	/*! 
	 * \brief Value of the damping factor for the correction prolongation.
	 * \return Value of the damping factor.
	 */	
	double GetDamp_Correc_Prolong(void);

	/*! 
	 * \brief Update the CFL number using the ramp information.
	 * \param[in] val_iter - Current solver iteration.
	 */
	void UpdateCFL(unsigned long val_iter);

	/*! 
	 * \brief Set the global parameters of each simulation for each runtime system.
	 * \param[in] val_solver - Solver of the simulation.
	 * \param[in] val_system - Runtime system that we are solving.
	 */
	void SetGlobalParam(unsigned short val_solver, unsigned short val_system, unsigned long val_extiter);

	/*!
	 * \brief Get information about converting a mesh from CGNS to SU2 format.
	 * \return <code>TRUE</code> if a conversion is requested; otherwise <code>FALSE</code>.
	 */
	bool GetCGNS_To_SU2(void);

	/*! 
	 * \brief Get information about whether a converted mesh should be written.
	 * \return <code>TRUE</code> if the converted mesh should be written; otherwise <code>FALSE</code>.
	 */
	bool GetWrite_Converted_Mesh(void);

  /*!
	 * \brief Value of the CFL reduction factor for the turbulence model.
	 * \return Value of the CFL reduction factor for the turbulence model.
	 */
	double GetTurb_CFLRedCoeff(void);
  
	/*!
	 * \brief Get the total pressure at an inlet boundary.
	 * \param[in] val_index - Index corresponding to the inlet boundary.
	 * \return The total pressure.
	 */
	double GetInlet_Ptotal(string val_index);
  
  /*!
	 * \brief Get the total temperature at an inlet boundary.
	 * \param[in] val_index - Index corresponding to the inlet boundary.
	 * \return The total temperature.
	 */
	double GetInlet_Ttotal(string val_index);

	/*!
	 * \brief Get the flow direction unit vector at an inlet boundary.
	 * \param[in] val_index - Index corresponding to the inlet boundary.
	 * \return The flow direction vector.
	 */
	double* GetInlet_FlowDir(string val_index);

	/*!
	 * \brief Get the back pressure (static) at an outlet boundary.
	 * \param[in] val_index - Index corresponding to the outlet boundary.
	 * \return The outlet pressure.
	 */
	double GetOutlet_Pressure(string val_index);

	/*!
	 * \brief Get the wall temperature (static) at an isothermal boundary.
	 * \param[in] val_index - Index corresponding to the isothermal boundary.
	 * \return The wall temperature.
	 */
	double GetIsothermal_Temperature(string val_index);

	/*!
	 * \brief Get the wall heat flux on a constant heat flux boundary.
	 * \param[in] val_index - Index corresponding to the constant heat flux boundary.
	 * \return The heat flux.
	 */
	double GetWall_HeatFlux(string val_index);

	/*!
	 * \brief Set the non-dimensionalization for SU2_CFD.
	 * \param[in] val_nDim - Number of dimensions for this particular problem.
	 * \param[in] val_rank - Processor rank.
	 * \param[in] val_iZone - Current grid domain number.
	 */	
	void SetNondimensionalization(unsigned short val_nDim);

  /*!
	 * \brief Set the config options.
	 */
	void SetConfig_Options(void);

  /*!
	 * \brief Set the config file parsing.
	 */
  void SetParsing(char case_filename[200]);

	/*! 
	 * \brief Config file postprocessing.
	 */	
	void SetPostprocessing(unsigned short val_software);

	/*! 
	 * \brief Config file markers processing.
	 */	
	void SetMarkers(unsigned short val_software);

	/*! 
	 * \brief Config file output.
	 */	
	void SetOutput(unsigned short val_software);

	/*!
	 * \brief Given arrays x[1..n] and y[1..n] containing a tabulated function, i.e., yi = f(xi), with
	          x1 < x2 < . . . < xN , and given values yp1 and ypn for the first derivative of the interpolating
	          function at points 1 and n, respectively, this routine returns an array y2[1..n] that contains
	          the second derivatives of the interpolating function at the tabulated points xi. If yp1 and/or
	          ypn are equal to 1 × 1030 or larger, the routine is signaled to set the corresponding boundary
	          condition for a natural spline, with zero second derivative on that boundary.
						Numerical Recipes: The Art of Scientific Computing, Third Edition in C++.
	 */
	void SetSpline(vector<double> &x, vector<double> &y, unsigned long n, double yp1, double ypn, vector<double> &y2);

	/*!
	 * \brief Given the arrays xa[1..n] and ya[1..n], which tabulate a function (with the xai’s in order),
	          and given the array y2a[1..n], which is the output from spline above, and given a value of
	          x, this routine returns a cubic-spline interpolated value y.
         	  Numerical Recipes: The Art of Scientific Computing, Third Edition in C++.
	 * \returns The interpolated value of for x.
	 */
	double GetSpline(vector<double> &xa, vector<double> &ya, vector<double> &y2a, unsigned long n, double x);
  
};

#include "config_structure.inl"
